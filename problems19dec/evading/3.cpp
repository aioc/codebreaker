#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;
int V, E, S, K;
int ans;

const int MAX_V = 1e5 + 5;

bool seen[MAX_V*2];

vector<int> adj[MAX_V*2];

void addEdge(int a, int b) {
    adj[a    ].push_back(b + V);
    adj[a + V].push_back(b    );
}

int main() {
    cin >> V >> E >> S >> K;
    for(int i = 0; i < E; i++) {
        int x, y;
        cin >> x >> y;
        addEdge(x, y);
        addEdge(y, x);
    }

    // Any vertex is reachable in at most V edges,
    // so clamp the value.
    if(K > V) {
        K = V + ((V^K)&1 ? 1 : 0);
    }

    // BFS
    vector<int> curq;
    curq.push_back(S);
    for(int i = 0; i <= K; i++) {
        vector<int> newq; 
        for(auto at: curq) {
            seen[at] = true;
            for(auto to: adj[at]) {
                if(!seen[to]) {
                    newq.push_back(to);
                }
            }
        }
        curq = newq;
    }

    for(int i = 1; i <= V; i++) {
        ans += seen[i + ((K%2 == 0) ? 0 : V)];
    }
    cout << ans << "\n";
    return 0;
}
