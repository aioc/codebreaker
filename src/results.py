import json
import problem
import problems
import time
import collections
import database
import random

CACHE = {}
SCOREBOARD = []

SELECT_USER_PROBLEM_TOTAL = '''
SELECT sum(score)
FROM results LEFT JOIN users
ON owner = users.username
WHERE complete = TRUE and username = $1 and problem = $2;
'''

SELECT_VISIBLE_NAMES = '''
SELECT username
FROM users
WHERE visible = TRUE;
'''

SELECT_SCOREBOARD_SCORES = '''
SELECT username, problem, score
FROM results LEFT JOIN users
ON owner = users.username
WHERE complete = TRUE AND id < $1
ORDER BY results.id ASC;
'''

async def get_user_problem_total(username, problem):
    result = await database.connection.fetchval(SELECT_USER_PROBLEM_TOTAL, username, problem)
    if result is None: result = 0
    return result

# Only update this every minute or so, because it'll be slow.
async def get_scoreboard():
    scores = {}
    scoreboard = []

    names = [result['username'] for result in await database.connection.fetch(SELECT_VISIBLE_NAMES)]
    probs = problems.get_alphabetical()

    for n in names:
        scores[n] = { p.short_name:[0] for p in probs}

    scoreboard_freeze_id = await database.connection.fetchval("SELECT value FROM settings WHERE name = 'scoreboard_freeze_id';")
    if scoreboard_freeze_id is None: scoreboard_freeze_id = 1000000000
    for result in await database.connection.fetch(SELECT_SCOREBOARD_SCORES, scoreboard_freeze_id):
        if result['username'] not in names: continue
        scores[result['username']][result['problem']].append(scores[result['username']][result['problem']][-1] + result['score'])

    for n in names:
        scoreboard.append({
            'name': n,
            'scores': [
                {
                    'problem': p.long_name,
                    'score': max(scores[n][p.short_name])
                } for p in probs
            ],
            'total': sum([max(scores[n][p.short_name]) for p in probs])
            })
    scoreboard.sort(key = lambda x: x['total'], reverse = True)
    return scoreboard
