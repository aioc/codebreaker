import os
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

    async def load_executables(self, se, be, coe, che):
        directory = os.path.dirname(__file__) + "/problems/"

        box = execute.Box()

        # Sanity
        with open(directory + se, "rb") as f:
            self.sanity_exe = f.read()

        if se.endswith('.cpp'):
            if se in binaries_cache.keys():
                self.sanity_exe = binaries_cache[se]
            else:
                cfile = box.prepfile('source.cpp', self.sanity_exe)
                efile = box.prepfile('a.exe')
                await box.run_command_async('g++ -O2 -std=c++11 -o %s %s' % (efile, cfile), timout=10)
                with open(efile, "rb") as f:
                    self.sanity_exe = f.read()
                binaries_cache[se] = self.sanity_exe

        # Broken
        with open(directory + be, "rb") as f:
            self.broken_exe = f.read()

        if be.endswith('.cpp'):
            if be in binaries_cache.keys():
                self.broken_exe = binaries_cache[be]
            else:
                cfile = box.prepfile('source.cpp', self.broken_exe)
                efile = box.prepfile('a.exe')
                await box.run_command_async('g++ -O2 -std=c++11 -o %s %s' % (efile, cfile), timeout=10)
                with open(efile, "rb") as f:
                    self.broken_exe = f.read()
                binaries_cache[be] = self.broken_exe

        # Correct
        with open(directory + coe, "rb") as f:
            self.correct_exe = f.read()

        if coe.endswith('.cpp'):
            if coe in binaries_cache.keys():
                self.correct_exe = binaries_cache[coe]
            else:
                cfile = box.prepfile('source.cpp', self.correct_exe)
                efile = box.prepfile('a.exe')
                await box.run_command_async('g++ -O2 -std=c++11 -o %s %s' % (efile, cfile), timeout=10)
                with open(efile, "rb") as f:
                    self.correct_exe = f.read()
                binaries_cache[coe] = self.correct_exe

        # Checker
        if che == '': che = 'match_file'
        with open(directory + che, "rb") as f:
            self.checker_exe = f.read()

        if che.endswith('.cpp'):
            if che in binaries_cache.keys():
                self.checker_exe = binaries_cache[che]
            else:
                cfile = box.prepfile('source.cpp', self.checker_exe)
                efile = box.prepfile('a.exe')
                await box.run_command_async('g++ -O2 -std=c++11 -o %s %s' % (efile, cfile), timeout=10)
                with open(efile, "rb") as f:
                    self.checker_exe = f.read()
                binaries_cache[che] = self.checker_exe


        box.cleanup()
