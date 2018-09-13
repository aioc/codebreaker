import asyncio
import asyncpg
import os


connection = None


async def connect():
    global connection
    dsn = os.environ.get('DATABASE_URL')
    if dsn:
        connection = await asyncpg.connect(dsn = dsn)
    else:
        connection = await asyncpg.connect(
            database = 'codebreaker'
        )


loop = asyncio.get_event_loop()
loop.run_until_complete(connect())
