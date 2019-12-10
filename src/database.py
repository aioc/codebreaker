import asyncio
import asyncpg
import getpass
import os


connection = None


async def connect():
    global connection
    connection = await asyncpg.connect(
        user = getpass.getuser(),
        database = 'codebreaker'
    )


loop = asyncio.get_event_loop()
loop.run_until_complete(connect())
