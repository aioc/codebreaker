import os, shutil
import execute

binaries_cache = {}

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
        directory = os.path.dirname(__file__) + "/problems/"
        with open(directory + tc, "r") as f:
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
        directory = os.path.dirname(__file__) + "/problems/"

        # Sanity
        se = directory + se
        if se.endswith('.cpp'):
            sf = se
            se = sf[:-4] + '.exe'
            r = await self.recompile_from_cpp(se, sf)
            if r: print(" > recompiled sanity")
        with open(se, "rb") as f:
            self.sanity_exe = f.read()

        # Broken
        be = directory + be
        if be.endswith('.cpp'):
            sf = be
            be = sf[:-4] + '.exe'
            r = await self.recompile_from_cpp(be, sf)
            if r: print(" > recompiled broken solution")
        with open(be, "rb") as f:
            self.broken_exe = f.read()

        # Correct
        coe = directory + coe
        if coe.endswith('.cpp'):
            sf = coe
            coe = sf[:-4] + '.exe'
            r = await self.recompile_from_cpp(coe, sf)
            if r: print(" > recompiled correct")
        with open(coe, "rb") as f:
            self.sanity_exe = f.read()

        # Checker
        if che == '': che = 'match_file'
        che = directory + che
        if che.endswith('.cpp'):
            sf = che
            che = sf[:-4] + '.exe'
            r = await self.recompile_from_cpp(che, sf)
            if r: print(" > recompiled checker")
        with open(che, "rb") as f:
            self.sanity_exe = f.read()
