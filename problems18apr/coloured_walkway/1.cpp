// NsqrtN solution
#include <bits/stdc++.h>
using namespace std;

const int MAX = 1e5+5;
const int THRESHOLD = (int)(312*1.4); // Empirically determined
const int MOD = 1e9+7;

int V, E, N;

// On update:
//  - For each adjacent large, update your count
//  - For each adjacent small, do nothing
// On query:
//  - If small, check all adjacent
//  - If large, read count


vector<int> adj[MAX];

// Adjacency list, but only lists large vertices
vector<int> adjlarge[MAX];

// Colour of i-th tile (from 0)
int c[MAX];

// Boolean is it large?
bool large[MAX];

// Cached count for large colours
int cache[MAX];

// Num ways to get from start to here
int cnt[MAX];

// Num ways to get to the current tile under consideration,
// where the second last tile is this colour.
int csum[MAX];

int main() {
    // Read input
    cin >> N >> V;
    for(int i = 1; i <= N; i++) {
        cin >> c[i];
    }
    cin >> E;
    for(int i = 0; i < E; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].emplace_back(b);
        adj[b].emplace_back(a);
    }

    // Determine large vertices
    for(int i = 1; i <= V; i++) {
        large[i] = adj[i].size() >= THRESHOLD;
    }

    // Precompute adjacent larges
    for(int i = 1; i <= V; i++) {
        for(auto x: adj[i]) {
            if(large[x]) {
                adjlarge[i].emplace_back(x);
            }
        }
    }
    
    // Do the DP
    for(int at = 1; at <= N; at++) {
        int curc = c[at];

        // Update DP value
        if(at == 1) {
            cnt[at] = 1;
        } else {
            if(large[curc]) {
                cnt[at] = cache[curc];
            } else {
                for(auto to: adj[curc]) {
                    cnt[at] += csum[to];
                    cnt[at] %= MOD;
                }
            }
        }

        // Update csum
        csum[curc] += cnt[at];
        csum[curc] %= MOD;

        // Update large caches
        for(auto x: adjlarge[curc]) {
            cache[x] += cnt[at];
            cache[x] %= MOD;
        }
    }

    cout << cnt[N] << "\n";
}
