#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;
const int INF = 1000000001;
// const int INF = 1'000'000'001;
int N, M;
int b[MAXN];
vector<int> allE[MAXN];

struct state {
    int city, best;
    bool operator<(const state &s) const {
        if (best == s.best) return city < s.city;
        return best < s.best;
    }
};

set<state> states;
int minB[MAXN];
bool done[MAXN];

bool canDo(int allowed) {
    for (int i = 0; i < N; i++) {
        minB[i] = INF;
        done[i] = false;
        states.insert({i, minB[i]});
    }
    minB[0] = 0;
    states.insert({0, b[0]});
    while (!states.empty()) {
        state cs = *(states.begin());
        states.erase(states.begin());
        if (cs.city == N-1 && cs.best != INF) return true;
        done[cs.city] = true;
        for (int nxt : allE[cs.city]) {
            if (cs.best - allowed > b[nxt]) continue;
            if (done[nxt]) continue;
            int newB = max(cs.best, b[nxt]);
            if (newB < minB[nxt]) {
                states.erase(states.find({nxt, minB[nxt]}));
                minB[nxt] = newB;
                states.insert({nxt, minB[nxt]});
            }
        }
    }
    return false;
}

int main() {
    scanf("%d %d", &N, &M);
    for (int i = 0; i < N; i++) {
        scanf("%d", &b[i]);
    }
    for (int i = 0; i < M; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        a--; b--;
        allE[a].push_back(b);
    }
    int lo = 0;
    //int hi = INF;
    int hi = 1 << 30;
    int mid, best;
    while (lo <= hi) {
        mid = (lo+hi)/2;
        if (canDo(mid)) {
            hi = mid-1;
            best = mid;
        } else {
            lo = mid+1;
        }
    }
    printf("%d\n", best);
    return 0;
}
