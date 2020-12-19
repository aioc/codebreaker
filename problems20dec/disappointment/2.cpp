#include <cstdio>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>

using namespace std;

typedef pair<int,int> pi;

int n, m;

int score[100005];

// an adjacency list for the graph
vector<int> g[100005];

// pq for the dijkstra
priority_queue<pi,vector<pi>,greater<pi>> q;

int d[100005]; //minimum bottle neck for each one.

bool checked[100005];

// honestly idk what i'm doing but this seems about right. 
bool dfs(int node, int x){
    if (checked[node]) return false;
    checked[node] = true;
    if (node == n) return true;

    for (int tgt : g[node]){
        if (max(d[node]-score[tgt],0) <= x){
            if (dfs(tgt,x)) return true;
        }
    }
    return false;
}

bool decision(int x){
    for (int i = 1; i <= n; i++){
        checked[i] = false;
    }
    return (dfs(1,x));
}

int main(){
    scanf("%d %d", &n, &m);

    for (int i = 1; i <= n; i++){
        scanf("%d", &score[i]);
        d[i] = 1e9+7;
    }
    
    for (int i = 0; i < m; i++){
        int tx, ty;
        scanf("%d %d", &tx, &ty);
        g[tx].push_back(ty);
    }
    // run a modified dijkstra to find the minimum bottleneck to each node
    d[1] = score[1];
    q.push({score[1],1});
    while (!q.empty()){
        auto cur = q.top();
        q.pop();
        if (checked[cur.second]) continue;
        checked[cur.second] = true;
        for (int tgt : g[cur.second]){
            if (checked[tgt]) continue;
            int t = max(cur.first, score[tgt]);
            if (t < d[tgt]){
                d[tgt] = t;
                q.push({t,tgt});
            }
        }
    }
    
    // bsearch the answer?
    int hi = 1e9 + 7;
    int lo = 0;
    int best = 1e9 +7;
    int mid;
    while (lo <= hi){
        mid = (hi + lo)/2;
        if (decision(mid)){
            hi = mid - 1;
            best = mid;
        }
        else{
            lo = mid + 1;
        }
    }
    printf("%d", best);
}
