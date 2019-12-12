#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;
int N, C;
vector<int> x;
int P;
int BUCK;
vector<int> cols;
vector<vector<int>> adj;
vector<vector<int>> pushE;
vector<vector<vector<int>>> tripleNested; // :O
map<vector<int>, map<vector<int>, map<vector<vector<int>>, map<vector<vector<vector<int>>>, map<vector<vector<vector<vector<vector<int>>>>>, map<vector<vector<vector<vector<vector<vector<vector<vector<int>>>>>>>>, int>>>>>> fibonacciNested; // :O :O :OO :OOO :OOOOOO :OOOOOOOO

int main() {
    scanf("%d %d", &N, &C);
    for (int i = 0; i < N; i++) {
        int _x;
        scanf("%d", &_x);
        x.push_back(_x);
    }
    scanf("%d", &P);
    BUCK = sqrt(P);
    set<int> adjVerts[C+1];
    for (int i = 0; i < P; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        adjVerts[a].insert(b);
        adjVerts[b].insert(a);
    }
    vector<bool> islarge;
    islarge.resize(C+1);
    for (int i = 1; i <= C; i++) {
        islarge[i] = adjVerts[i].size() > BUCK;
    }
    adj.resize(C+1);
    pushE.resize(C+1);
    for (int i = 1; i <= C; i++) {
        for (int j : adjVerts[i]) {
            if (islarge[j]) pushE[i].push_back(j);
            adj[i].push_back(j);
        }
    }

    vector<int> dp(C+1, 0);
    vector<int> forwardDp(C+1, 0);
    for (int i = 0; i< N; i++) {
        int cAns = i == 0 ? 1 :0; // :0
        int cc = x[i];
        if (islarge[cc]) cAns = (cAns + forwardDp[cc]) % MOD;
        else {
            for (int p : adj[cc]) cAns += dp[p];
            cAns %= MOD;
        }
        for (int nxt : pushE[cc]) {
            forwardDp[nxt] = (cAns + forwardDp[nxt]) % MOD;
        }
        dp[cc] = (dp[cc] + cAns) % MOD;
        if (i == N-1) {
            printf("%d\n", cAns);
            return 0;
        }
    }
    return 0;
}
