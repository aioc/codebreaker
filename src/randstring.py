import random
import string

POOL = list(string.ascii_lowercase + string.digits)

def generate(length):
    return ''.join(random.choice(POOL) for i in range(length))
