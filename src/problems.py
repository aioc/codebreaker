import os, shutil, json
import execute

PROBLEM_DIR = "problems20dec"

class Problem:

    long_name = 'The Name of the Problem'
    short_name = 'problem'
    task_code = 'no code'

    sanity_exe = ''
    broken_exe = ''
    correct_exe = ''
    checker_exe = ''

    def __init__(self, ln, sn, tc, is_interactive):
        self.long_name = ln
        self.short_name = sn
        self.is_interactive = is_interactive
        with open(os.path.join(os.getcwd(), PROBLEM_DIR, tc), "r") as f:
            self.task_code = f.read()

    def load_executables(self, se, be, coe, che):
        directory = os.path.join(os.getcwd(), PROBLEM_DIR)

        # Sanity
        se = os.path.join(directory,se)
        if se.endswith('.cpp'):
            se = se[:-4] + '.exe'
        with open(se, "rb") as f:
            self.sanity_exe = f.read()

        # Broken
        be = os.path.join(directory,be)
        if be.endswith('.cpp'):
            be = be[:-4] + '.exe'
        with open(be, "rb") as f:
            self.broken_exe = f.read()

        # Correct
        coe = os.path.join(directory,coe)
        if coe.endswith('.cpp'):
            coe = coe[:-4] + '.exe'
        with open(coe, "rb") as f:
            self.correct_exe = f.read()

        # Checker
        if che == '': che = 'match_file'
        che = os.path.join(directory,che)
        if che.endswith('.cpp'):
            che = che[:-4] + '.exe'
        with open(che, "rb") as f:
            self.checker_exe = f.read()

problems = []
problem_dict = {}

def load_problem_info():
    global problems
    global problem_dict
    problems = []
    problem_dict = {}
    with open(os.path.join(os.getcwd(), PROBLEM_DIR, 'problems.json'), 'r') as f:
        problems = json.load(f)
    for d in problems:
        is_interactive = 'graders' in d or 'headers' in d
        p = Problem(d['long_name'], d['short_name'], d['task_code'], is_interactive)
        assert(p.short_name not in problem_dict)
        problem_dict[p.short_name] = p

async def compile_problem_executables():
    box = execute.Box()
    for d in problems:
        for sf in [d['sanity_exe'], d['broken_exe'], d['correct_exe'], d['checker_exe']]:
            sf = os.path.join(PROBLEM_DIR,sf)
            assert(os.path.isfile(sf))
            if sf.endswith('.cpp'):
                ef = sf[:-4] + '.exe'
                if os.path.isfile(ef) and os.path.getmtime(ef) > os.path.getmtime(sf): continue

                code_files = []

                def add_file_to_box(file_path, file_name, is_header = False):
                    with open(file_path, "rb") as sc:
                        cfile = box.prepfile(file_name, sc.read())
                        if not is_header:
                            code_files.append(cfile)

                add_file_to_box(sf, 'source.cpp')

                # include graders and headers, if necessary
                for file_type, is_header in [('headers', True), ('graders', False)]:
                    if file_type in d:
                        for file in d[file_type]:
                            file_path = os.path.join(PROBLEM_DIR,file)
                            assert(os.path.isfile(file_path))
                            file_name = file.split('/')[-1]
                            add_file_to_box(file_path, file_name, is_header)

                efile = box.prepfile('a.exe')
                await box.run_command_async(f'g++ -O2 -std=c++11 -o {efile} {" ".join(code_files)}', timeout=10)
                shutil.copy2(efile,ef)
                print("recompiled %s" % (sf))
    box.cleanup()

def load_problem_executables():
    # assumes other bits already loaded
    for d in problems:
        print("Loading %s" % (d['short_name']))
        problem_dict[d['short_name']].load_executables(d['sanity_exe'], d['broken_exe'], d['correct_exe'], d['checker_exe'])

def get_problem(name):
    return problem_dict[name]

def listing():
    return list(problem_dict)

def get_alphabetical():
    l = list(problem_dict.values())
    l.sort(key = lambda x: x.short_name)
    return l
