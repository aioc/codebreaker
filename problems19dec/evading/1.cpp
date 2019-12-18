#include <bits/stdc++.h>
using namespace std;

// Adjacency list
vector<int> ch[100005];

// dis[x][y] = The least hops you need to
// take to get from the start to vertex x,
// with parity y (y = 0 means an even
// number of hops, y = 1 means odd number
// of hops)
int dis[100005][2];
int n, e, x, k;
int ans;

int main() {
    scanf("%d%d%d%d", &n, &e, &x, &k);
    for (int i = 1; i <= n; i++) {
        int a, b; scanf("%d%d", &a, &b);
        ch[a].push_back(b);
        ch[b].push_back(a);
    }

    for (int i = 1; i <= n; i++) {
        // Use k+1 as "unseen"
        dis[i][0] = dis[i][1] = k + 1;
    }
    // First is vertex at, second is distance
    // (which also contains the parity information)
    queue<pair<int, int> > q;

    // BFS, on state exploded graph. Each vertex is split into
    // two vertices, one for odd parity and one for even parity.
    dis[x][0] = 0;
    q.emplace(x, 0);

    while (!q.empty()) {
        auto u(q.front()); q.pop();
        // If we can reach this vertex with the correct parity,
        // increment the answer.
        //
        // Wow k&1 sure looks like a weird way of saying k is odd.
        if (u.second == (k&1)) {
            ans++;
        }
        // Make sure to stop after k edges.
        if (dis[u.first][u.second] < k) {
            for (int v: ch[u.first]) {
                // Can't this be replaced with dis[v][!u.second] != k+1?
                if (dis[u.first][u.second]+1 < dis[v][!u.second]) {
                    dis[v][!u.second] = dis[u.first][u.second] + 1;
                    // Going along an edge always changes parity.
                    q.emplace(v, !u.second);
                }
            }
        }
    }

    printf("%d\n", ans);
    return 0;
}
