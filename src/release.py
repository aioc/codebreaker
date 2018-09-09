import asyncio
import problems

problems.load_problem_info()
asyncio.run_until_complete(problems.compile_problem_executables)
