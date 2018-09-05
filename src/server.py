import jinja2
import aiohttp
import aiohttp.web
import asyncio
import aiohttp_jinja2
import pygments
import pygments.lexers
import pygments.formatters
import os
import problems
import jwt
import datetime
import results
import database


TOKEN_SECRET = 'nobody-expects-the-spanish-inquisition'
ADMIN_ACCOUNT = 'admin'
USERS = {
    'admin',
    'user'
}


SELECT_SETTING = '''
SELECT value
FROM settings
WHERE name = $1;
'''

loop = asyncio.get_event_loop()
app = aiohttp.web.Application(loop = loop)


app.router.add_static('/static', './static')

aiohttp_jinja2.setup(app,
    loader = jinja2.FileSystemLoader('./templates/'),
    autoescape = jinja2.select_autoescape(['html', 'xml', 'j2']),
    filters = {
    }
)

def static_template(filepath):
    @aiohttp_jinja2.template(filepath)
    async def internal(request):
        return {}
    return internal


#app.router.add_get('/info/compilation', static_template('info_compilation.j2'))
#pp.router.add_get('/info/lang_docs', static_template('info_lang_docs.j2'))


@aiohttp_jinja2.template('index.j2')
async def page_login(request):
    error = request.rel_url.query.get('error', False)
    return {'error': bool(error)}
app.router.add_get('/', page_login)



def require_login_decorate(function, admin = False):
    async def replacement(request):
        token = request.cookies.get('login-token')
        if token != None:
            decoded = jwt.decode(token, TOKEN_SECRET, algorithm = 'HS256')
            if decoded:
                if not admin or decoded.get('admin'):
                    username = decoded['user']
                    request._username = username
                    request._display_name = decoded.get('display_name', username)
                    request._admin = decoded.get('admin', False)
                    result = await function(request)
                    if isinstance(result, dict):
                        result['username'] = username
                        result['password'] = password
                    return result
                else:
                    return aiohttp.web.HTTPForbidden()
        return aiohttp.web.HTTPSeeOther('/')
    replacement.__name__ = function.__name__
    return replacement


def require_login(function):
    return require_login_decorate(function)

def require_admin(function):
    return require_login_decorate(function, True)

SELECT_RESULTS = '''
SELECT score, status, complete, id
FROM results
WHERE owner = $1 AND problem = $2;
'''

SELECT_COMPLETED_PROBLEMS = '''
SELECT DISTINCT problem
FROM results
WHERE score > 0 AND owner = $1;
'''

@require_login
@aiohttp_jinja2.template('problem.j2')
async def page_problem_description(request):
    name = request.match_info['name']
    problem = problems.get_problem(name)
    res = await database.connection.fetch(SELECT_RESULTS, request._username, name)
    completed = await database.connection.fetch(SELECT_COMPLETED_PROBLEMS, request._username)
    completed = {r['problem'] for r in completed}
    best_score = 0
    for i in res:
        best_score = max(best_score, i['score'])

    submissions_allowed = await database.connection.fetchval(SELECT_SETTING, 'submissions_allowed')

    mark_it = submissions_allowed == 2 or (submissions_allowed == 1 and await results.get_user_problem_total(request._username, problem.short_name) > -20)

    return {
        'problem': problem,
        'code': pygments.highlight(problem.task_code, pygments.lexers.PythonLexer(), pygments.formatters.HtmlFormatter()),
        'can_submit': mark_it,
        'submit_message': ["We are currently not accepting submissions.", "You cannot submit any more attempts for this problem.",""][submissions_allowed],
        'results': res[::-1],
        'best_score': best_score,
        'username': request._display_name,
        'problems': problems.get_alphabetical(),
        'completed': completed
    }
app.router.add_get('/problem/{name}', page_problem_description)


@require_admin
@aiohttp_jinja2.template('admin.j2')
async def page_admin(request):
    return {}
app.router.add_get('/admin', page_admin)


async def get_token_cookie(username, password):
    user = await database.connection.fetchrow('SELECT * FROM users WHERE username = $1 AND password = $2;', username, password)
    if user is not None and user['password'] == password:
        datablob = {
            'user': username,
            'admin': user['admin'],
            'display_name': user['username'],
            'exp': datetime.datetime.utcnow() + datetime.timedelta(hours = 72)
        }
        return jwt.encode(datablob, TOKEN_SECRET, algorithm = 'HS256').decode('utf-8')


async def page_login_post(request):
    req = await request.post()
    username = req.get('username')
    password = req.get('password')
    token = await get_token_cookie(username, password)
    if token is not None:
        status = aiohttp.web.HTTPSeeOther('/problem/' + problems.get_alphabetical()[0].short_name)
        status.set_cookie('login-token', token, max_age = 72 * 60 * 60)
        print("LOGIN: %s" % (username))
        return status
    return aiohttp.web.HTTPSeeOther('/?error=yeah_there_was_one_of_those_sorry')
app.router.add_post('/login', page_login_post)

def relines(s):
    return '\n'.join(filter(len, s.split('\n')))

ENQUE_TASK = '''
INSERT INTO results
(owner, score, status, problem, complete, proposed_input, correct_output)
VALUES
($1, 0, 'In queue', $2, FALSE, $3, $4);
'''

@require_login
async def page_submit(request):
    username = request._username
    name = request.match_info['name']
    postdata = await request.post()
    proposed_input = postdata['proposed_input'].strip()
    correct_output = postdata['correct_output'].strip()
    problem = problem.get_problem(name)

    if proposed_input != "" or correct_output != "":
        submissions_allowed = await database.connection.fetchval(SELECT_SETTING, 'submissions_allowed')

        mark_it = submissions_allowed == 2 or (submissions_allowed == 1 and await results.get_user_problem_total(username, problem.short_name) > -20)

        print("SUBMISSION: %s %s [%s]" % (username, problem.short_name, "added to queue" if mark_it else ["ignored: submissions banned right now","ignored: too many points lost for this problem"][submissions_allowed]))

        if mark_it:
            # Enqueue the task
            await database.connection.execute(ENQUE_TASK, username, name, proposed_input, correct_output)
            await asyncio.sleep(2)
    return aiohttp.web.HTTPSeeOther('/problem/' + name)
app.router.add_post('/submit/{name}', page_submit)


@require_login
@aiohttp_jinja2.template('submission.j2')
async def page_submission(request):
    sql = 'SELECT proposed_input, correct_output, owner FROM results WHERE id = $1'
    row = await database.connection.fetchrow(sql, int(request.match_info['id']))
    allow = (row['owner'] == request._username) or request._admin
    return {
        'proposed_input': row['proposed_input'] if allow else 'Could not find anything :(',
        'correct_output': row['correct_output'] if allow else 'Could not find anything :('
    }
app.router.add_get('/submission/{id}', page_submission)

@aiohttp_jinja2.template('scoreboard.j2')
async def page_scoreboard(request):
    p = problems.get_alphabetical()
    g = []
    for i in p:
        s = ' '.join(i.long_name.split()[:-1])
        if s not in g: g.append(s)

    return {
            'groups': [{'name': i, 'num': sum(i in j.long_name for j in p)} for i in g],
            'problem_ids': [i.long_name.split()[-1] for i in p],
            'scores': await results.get_scoreboard()
    }
app.router.add_get('/scoreboard', page_scoreboard)


@require_admin
@aiohttp_jinja2.template('queue.j2')
async def page_queue(request):
    res = await database.connection.fetch('SELECT * FROM results ORDER BY id DESC LIMIT 100')
    return {
        'results': res[::-1]
    }
app.router.add_get('/queue', page_queue)


if __name__ == '__main__':
    problems.load_problems()
    p = os.getenv('PORT')
    aiohttp.web.run_app(app, host = '0.0.0.0', port = int(p) if p else 5001)
