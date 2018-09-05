import os, shutil, json
import execute

class Problem:

    long_name = 'The Name of the Problem'
    short_name = 'problem'
    task_code = 'no code'

    sanity_exe = ''
    broken_exe = ''
    correct_exe = ''
    checker_exe = ''

    def __init__(self, ln, sn, tc):
        self.long_name = ln
        self.short_name = sn
        with open(os.path.join(os.getcwd(), "problems", tc), "r") as f:
            self.task_code = f.read()

    async def recompile_from_cpp(self, ef, sf):
        assert(os.path.isfile(sf))
        if os.path.isfile(ef) and os.path.getmtime(ef) > os.path.getmtime(sf): return False
        box = execute.Box()
        with open(sf, "rb") as sc:
            cfile = box.prepfile('source.cpp', sc.read())
        efile = box.prepfile('a.exe')
        await box.run_command_async('g++ -O2 -std=c++11 -o %s %s' % (efile, cfile), timeout=10)
        shutil.copy2(efile,ef)
        box.cleanup()
        return True

    async def load_executables(self, se, be, coe, che):
        directory = os.path.join(os.getcwd(), "problems")

        # Sanity
        se = os.path.join(directory,se)
        if se.endswith('.cpp'):
            sf = se
            se = sf[:-4] + '.exe'
            r = await self.recompile_from_cpp(se, sf)
            if r: print(" > recompiled sanity")
        with open(se, "rb") as f:
            self.sanity_exe = f.read()

        # Broken
        be = os.path.join(directory,be)
        if be.endswith('.cpp'):
            sf = be
            be = sf[:-4] + '.exe'
            r = await self.recompile_from_cpp(be, sf)
            if r: print(" > recompiled broken solution")
        with open(be, "rb") as f:
            self.broken_exe = f.read()

        # Correct
        coe = os.path.join(directory,coe)
        if coe.endswith('.cpp'):
            sf = coe
            coe = sf[:-4] + '.exe'
            r = await self.recompile_from_cpp(coe, sf)
            if r: print(" > recompiled correct")
        with open(coe, "rb") as f:
            self.sanity_exe = f.read()

        # Checker
        if che == '': che = 'match_file'
        che = os.path.join(directory,che)
        if che.endswith('.cpp'):
            sf = che
            che = sf[:-4] + '.exe'
            r = await self.recompile_from_cpp(che, sf)
            if r: print(" > recompiled checker")
        with open(che, "rb") as f:
            self.sanity_exe = f.read()

problems = []
problem_dict = {}

def load_problems():
    global problems
    with open(os.path.join(os.getcwd(),'problems/problems.json'), 'r') as f:
        problems = json.load(f)
    for d in problems:
        p = Problem(d['long_name'], d['short_name'], d['task_code'])
        assert(p.short_name not in problem_dict)
        problem_dict[p.short_name] = p

async def compile_problems():
    for d in problems:
        print("Loading %s" % (d['short_name']))
        await problem_dict[d['short_name']].load_executables(d['sanity_exe'], d['broken_exe'], d['correct_exe'], d['checker_exe'])

def get_problem(name):
    return problem_dict[name]

def listing():
    return list(problem_dict)

def get_alphabetical():
    l = list(problem_dict.values())
    l.sort(key = lambda x: x.short_name)
    return l
