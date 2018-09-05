import asyncio
import subprocess
import os
import stat
import shlex
import randstring
import shutil

class TimeoutExpired(Exception):
    pass

class NonZeroReturnCode(Exception):
    pass


def mkdir(p):
    if not os.path.exists(p):
        os.makedirs(p)


class Box:

    def __init__(self):
        self.path = './temp/{}/'.format(randstring.generate(32))
        mkdir(self.path)

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
        process = subprocess.Popen(shlex.split(command), stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        try:
            process.stdin.write(input.encode('utf-8'))
            process.stdin.close()
        except:
            raise NonZeroReturnCode()
        for i in range(int(timeout / INTERVAL)):
            await asyncio.sleep(INTERVAL)
            retcode = process.poll()
            if retcode is not None:
                break
        if retcode is None:
            process.terminate()
            # Give the system a change to free the program's resources.
            raise TimeoutExpired
            # raise subprocess.TimeoutExpired(command, timeout, process.stdout, process.stderr)
        if retcode != 0:
            print(process.stderr.read().decode('utf-8'))
            raise NonZeroReturnCode()
        # raise subprocess.CalledProcessError(retcode, command, process.stdout, process.stderr)
        return process.stdout.read().decode('utf-8')

    def cleanup(self):
        shutil.rmtree(self.path)
