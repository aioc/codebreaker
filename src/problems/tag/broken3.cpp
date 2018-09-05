#include <iostream>
#include <vector>
using namespace std;

bool leaf[123456];
vector<int> adj[123456];

int V, E, ans;

int dfs(int x) {
    ans = 0;
    for(auto to: adj[x]) {
        if(ans == 0) {
            if(leaf[to]) {
                ans = 1;
            } else {
                int y = dfs(to);
                ans = y;
            }
        } else {
            if(leaf[to]) {
                ans += 1;
            } else {
                int y = dfs(to);
                ans += y;
            }
        }
    }
    if(leaf[x]) {
        return 1;
    }
    ans++;
    return ans;
}

int main() {
    scanf("%d %d\n", &V, &E);
    for(int i = 1; i <= V; i++) {
        leaf[i] = true;
    }
    for(int i = 0; i < E; i++) {
        int from, to;
        scanf("%d %d",  &from, &to);
        adj[from].push_back(to);
        leaf[from] = false;
    }
    int x = dfs(1);
    int y = E - x + 2;
    printf("%d %d\n", x, y);
}
