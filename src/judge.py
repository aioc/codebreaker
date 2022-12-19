import execute
import random
import traceback

# input sanity checker: prints 1 if valid
# correct checker: prints 1 if valid

# Returns score, status_message
async def run_judge(problem, user_input, user_output):
    box = execute.Box()

    sanity_exe = box.prepfile('sanity', problem.sanity_exe)
    try:
        result = await box.run_command_async(sanity_exe, timeout=10, input = user_input)
        if result.strip() != "1":
            return (0, "Input is insane.")
    except:
        box.cleanup()
        return (0, "[internal error: sanity checker failed]")

    broken_exe = box.prepfile('broken.exe', problem.broken_exe)
    correct_exe = box.prepfile('correct.exe', problem.correct_exe)

    try:
        broken_output = await box.run_command_async(broken_exe, timeout=2, input = user_input)
        broken_output = broken_output.strip()
    except execute.TimeoutExpired:
        return (10, "Code broken! (TLE)")
        box.cleanup()
    except execute.NonZeroReturnCode:
        return (10, "Code broken! (RE)")
        box.cleanup()

    try:
        correct_output = await box.run_command_async(correct_exe, input = user_input)
        correct_output = correct_output.strip()
    except:
        box.cleanup()
        return (0, "[internal error: judges' solution failed]")

    user_input_file = box.prepfile('user.in', user_input)
    user_output_file = box.prepfile('user.out', user_output)
    broken_output_file = box.prepfile('broken.out', broken_output)
    correct_output_file = box.prepfile('correct.out', correct_output)
    checker_exe = box.prepfile('checker', problem.checker_exe)

    try:
        result = await box.run_command_async("%s %s %s %s" % (checker_exe, user_output_file, correct_output_file, user_input_file))
        print(result)
        if result.strip() != "100":
            #box.cleanup()
            return (-1, "Wrong answer for proposed input.")
    except:
        box.cleanup()
        return (0, "[internal error: checker broke when marking user output]")

    try:
        result = await box.run_command_async("%s %s %s %s" % (checker_exe, broken_output_file, correct_output_file, user_input_file))
        if result.strip() == "100":
            box.cleanup()
            return (-2, "Input does not break code.")
    except:
        box.cleanup()
        return (0, "[internal error: checker broke when marking broken output]")

    return (10, "Code broken! (WA)")
