import problem

problem_dict = {}

# Long name
# Short name (also subdirectory with files)
# Code file
# sanity exe
# broken exe
# correct exe / checker exe
# True if checker, False if simple match

def problem_gen(ln, sn, d, ic, n):
    o = []
    for i in range(1,n+1):
        o.append({
            "long_name":ln + str(i),
            "short_name":sn + str(i),
            "task_code":"%s/broken%d.cpp" % (d, i),
            "sanity_exe":"%s/sanity" % (d),
            "broken_exe":"%s/broken%d.cpp" % (d, i),
            "correct_exe":"%s/correct.cpp" % (d),
            "checker_exe":"%s/checker" % (d) if ic else "match_file"
        })
    return o

problems = []
problems.extend(problem_gen("Coconut ", "a5-coconut-", "coconut", False, 3))
problems.extend(problem_gen("Mango ", "a1-mango-", "mango", False, 4))
problems.extend(problem_gen("LSC ", "a6-lollipop-", "lollipop", True, 1))
problems.extend(problem_gen("Chimera ", "a4-chimera-", "chimera", False, 3))
problems.extend(problem_gen("Tag ", "a2-tag-", "tag", False, 4))
problems.extend(problem_gen("Snake ", "a3-snake-", "snake", True, 2))
problems.extend(problem_gen("Maria ", "b2-maria-", "maria", False, 1))
problems.extend(problem_gen("Greed ", "c2-greed-", "greed", False, 1))

def add_problems():
    for d in problems:
        p = problem.Problem(d['long_name'], d['short_name'], d['task_code'])
        assert(p.short_name not in problem_dict)
        problem_dict[p.short_name] = p

async def compile_problems():
    for d in problems:
        await problem_dict[d['short_name']].load_executables(d['sanity_exe'], d['broken_exe'], d['correct_exe'], d['checker_exe'])
        print("Compiled", d['short_name'])


def get(name):
    return problem_dict[name]

def listing():
    return list(problem_dict)

def get_alphabetical():
    l = list(problem_dict.values())
    l.sort(key = lambda x: x.short_name)
    return l
