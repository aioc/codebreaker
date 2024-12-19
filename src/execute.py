import asyncio
import subprocess
import os
import stat
import shlex
import randstring
import shutil
import sys

class TimeoutExpired(Exception):
    pass

class NonZeroReturnCode(Exception):
    pass


def mkdir(p):
    if not os.path.exists(p):
        os.makedirs(p)


class Box:

    # Creates a temporary directory to perform compilation in, so that
    # compilation artifacts can easily be cleaned up.
    #
    # This is not secure for compiling untrusted code!
    def __init__(self):
        self.path = './temp/{}/'.format(randstring.generate(32))
        mkdir(self.path)

    # Returns the absolute path to the given file
    # (but does not guarantee that it exists).
    #
    # If content is not None, also creates the file and fills it with
    # content. If the file already exists, it is overwritten.
    def prepfile(self, name, content = None):
        location = self.path + name
        if type(content) == str:
            content = content.encode('utf-8')
        if content is not None:
            with open(location, 'wb') as f:
                f.write(content)
            st = os.stat(location)
            os.chmod(location, st.st_mode | stat.S_IEXEC)
        return location

    async def run_command_async(self, command, timeout = 3, input = ''):
        INTERVAL = 0.25
        sys.stdout.write("Attempting %s\n" % command) 
        sys.stdout.write("cwd %s\n" % os.getcwd()) 
        process = subprocess.Popen(shlex.split(command), stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        try:
            out, err = process.communicate(input=input.encode('utf-8'), timeout=timeout)
            if process.returncode != 0:
                raise NonZeroReturnCode()
        except subprocess.TimeoutExpired as e:
            raise TimeoutExpired()
        except Exception as e:
            raise NonZeroReturnCode()
        return out.decode('utf-8');

    def cleanup(self):
        shutil.rmtree(self.path)
