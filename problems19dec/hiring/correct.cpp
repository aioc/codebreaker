#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void readVector(vector<int> &v) {
    int N;
    scanf("%d", &N);
    for(int i = 0; i < N; i++) {
        int x;
        scanf(" %d ", &x);
        v.push_back(x);
    }
}

int ans;

vector<int> pairOff(vector<int> skills, vector<int> master) {
    sort(skills.begin(), skills.end());
    sort(master.begin(), master.end());
    while(master.size() && skills.size()) {
        int lastSkill = *skills.rbegin();
        int lastMaster = *master.rbegin();
        //cerr << "Considering";
        //cerr << lastSkill << " gets job " << lastMaster << " ";
        if(lastSkill >= lastMaster) {
            //cerr << " success!\n";
            skills.pop_back();
            master.pop_back();
            ans++;
        } else {
            //cerr << " failure\n";
            master.pop_back();
        }
    }
    return skills;
}

int main() {
    vector<int> skills;
    vector<int> student;
    vector<int> master;

    readVector(skills);
    readVector(student);
    readVector(master);

    skills = pairOff(skills, master);
    for(auto &x: skills) {
        x *= -1;
    }
    for(auto &x: student) {
        x *= -1;
    }
    pairOff(skills, student);
    printf("%d\n", ans);
}
