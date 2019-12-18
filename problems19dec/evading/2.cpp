#include <bits/stdc++.h>
using namespace std;

int dist[100005][2];
vector<int> adj[100005];
int CITIES, HOPS, START, K;
int not_std_count;

void dfs(int at, int far) {
    if (dist[at][far&1] <= K) {
        return;
    }
    dist[at][far&1] = far;
    if ((far&1) == (K&1)) {
        not_std_count++;
    }
    if (far < K) {
        for (int u: adj[at]) {
            dfs(u, far+1);
        }
    }
}

int main() {
    scanf("%d%d%d%d", &CITIES, &HOPS, &START, &K);
    for (int i = 1; i <= HOPS; i++) {
        int a, b; scanf("%d%d", &a, &b);
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    for (int i = 1; i <= CITIES; i++) {
        dist[i][0] = dist[i][1] = K + 1;
    }
    dfs(START, 0);
    printf("%d\n", not_std_count);
    return 0;
}
