import asyncio
import problems

problems.load_problem_info()
loop = asyncio.get_event_loop()
compile_task = loop.create_task(problems.compile_problem_executables())
loop.run_until_complete(compile_task)
