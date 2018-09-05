import os
import time
import signal
import json
import asyncio
import sys
import random
os.chdir(os.path.join(os.path.dirname(__file__),".."))
import database
import judge
import problems

UPDATE_COMPLETED = '''
UPDATE results
SET status = $3, score = $2, complete = TRUE
WHERE id = $1 AND complete = FALSE;
'''

should_run = True

async def run_worker(number):
    while should_run:
        jobs_to_do = await database.connection.fetch('SELECT * FROM results WHERE complete = FALSE')
        # Oh wow what a nice queue
        if len(jobs_to_do) > 0:
            job = random.choice(jobs_to_do)
            print('Processing job -', job['id'])
            problem = problems.get_problem(job['problem'])
            score, status = await judge.run_judge(problem, job['proposed_input'], job['correct_output'])
            await database.connection.execute(UPDATE_COMPLETED, job['id'], int(score), status)
            print('Finished -', status)
        else:
            await asyncio.sleep(0.3)

def handle_sigterm(a, b):
    global should_run
    should_run = False
    print('Caught sigterm, stopping...')

def handle_sigint(a, b):
    global should_run
    should_run = False
    print('Caught sigint, stopping...')

if __name__ == '__main__':
    print('Started')
    signal.signal(signal.SIGTERM, handle_sigterm)
    signal.signal(signal.SIGINT, handle_sigint)
    num_threads = 1 if len(sys.argv) == 1 else int(sys.argv[1])

    problems.load_problems()
    compile_loop = asyncio.get_event_loop()
    task = compile_loop.create_task(problems.compile_problems())
    compile_loop.run_until_complete(task)

    loop = asyncio.get_event_loop()
    worker_list = [
        asyncio.ensure_future(run_worker(i)) for i in range(num_threads)
    ]
    loop.run_until_complete(asyncio.wait(worker_list))
    loop.close()
