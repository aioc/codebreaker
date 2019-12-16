#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void readVector(vector<int> &v, int K) {
    // I should switch to cin/cout before
    // Matt gives me a personal How To Code It talk.
    for(int i = 0; i < K; i++) {
        int x;
        scanf(" %d ", &x);
        v.push_back(x);
    }
}

int ans;
int N, S, M;

vector<int> pairOff(vector<int> skills, vector<int> master) {
    sort(skills.begin(), skills.end());
    sort(master.begin(), master.end());

    while(master.size() && skills.size()) {
        // v.begin() is an iterator to the start,
        // v.rbegin() is the "reverse" iterator, that is,
        // to the end of the vector.
        //
        // I'm using rbegin() here because I'm too lazy to type
        // v[v.size()-1] to get the last element.
        //
        // Matt would be proud (I think)
        int lastSkill = *skills.rbegin();
        int lastMaster = *master.rbegin();

        // If the highest skill monk can take the highest
        // requirement master job, let them!
        if(lastSkill >= lastMaster) {
            skills.pop_back();
            master.pop_back();
            N--;
            ans++;
        } else {
            // Otherwise, this master job is too hard... throw it out!
            master.pop_back();
        }
    }

    // Return all the monks who have not been assigned jobs.
    return skills;
}

int main() {
    vector<int> skills;
    vector<int> student;
    vector<int> master;

    scanf("%d", &N);
    readVector(skills, N);
    scanf("%d", &S);
    readVector(student, S);
    scanf("%d", &M);
    readVector(master, M);

    // Firstly, assign master jobs using the greedy principle
    skills = pairOff(skills, master);

    // Then, assign student jobs using the greedy principle.
    // If we flip the skill values of monks and the skill value
    // requirement of student roles (so they're negative),
    // then the student requirement becomes a master requirement,
    // which means we can reuse the master code.
    for(int i = 0; i < N-1; i++) {
        skills[i] *= -1;
    }
    for(int i = 0; i < S; i++) {
        student[i] *= -1;
    }
    // I can hear the faint voice of Matt telling me I'll regret
    // not using std::transform.
    //
    // Good thing my code is definitely bug free.

    pairOff(skills, student);
    printf("%d\n", ans);
}
