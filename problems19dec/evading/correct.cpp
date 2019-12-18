#include <bits/stdc++.h>
using namespace std;

vector<int> ch[100005];
int dis[100005][2];
int n, e, x, k;
int ans;

int main() {
    scanf("%d%d%d%d", &n, &e, &x, &k);
    for (int i = 1; i <= e; i++) {
        int a, b; scanf("%d%d", &a, &b);
        ch[a].push_back(b);
        ch[b].push_back(a);
    }

    for (int i = 1; i <= n; i++) {
        dis[i][0] = dis[i][1] = k + 1;
    }
    queue<pair<int, int> > q;

    dis[x][0] = 0;
    q.emplace(x, 0);

    while (!q.empty()) {
        auto u(q.front()); q.pop();
        if (u.second == (k&1)) {
            ans++;
        }
        if (dis[u.first][u.second] < k) {
            for (int v: ch[u.first]) {
                if (dis[u.first][u.second]+1 < dis[v][!u.second]) {
                    dis[v][!u.second] = dis[u.first][u.second] + 1;
                    q.emplace(v, !u.second);
                }
            }
        }
    }

    printf("%d\n", ans);
    return 0;
}
