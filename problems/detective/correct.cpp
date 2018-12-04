#include <bits/stdc++.h>
using namespace std;

int N, M;
vector<pair<int,int>> adj[100005];
bool banned[100005];

vector<pair<int,int>> components;
bool both_sides_accuse = 0;

int accuses[2] = {0,0};
set<int> accuse_set[2];
bool seen[100005];
int parity[100005];
vector<int> accuse_list[2];
bool scan_component(int n, int p) {
    bool pass = 1;
    if (seen[n]) return parity[n] == p;
    seen[n] = 1;
    parity[n] = p;
    for (auto i : adj[n]) {
        if (i.second == 3) {
            accuse_list[p].push_back(i.first);
            if (accuses[p] != 0 && accuses[p] != i.first) {
                banned[i.first] = 1;
                if (accuses[p] > 0) banned[accuses[p]] = 1;
                accuses[p] = -1;
            } else {
                accuses[p] = i.first;
            }
        } else {
            pass &= scan_component(i.first, i.second == 1 ? p:1-p);
        }
    }
    return pass;
}

int main() {
    scanf("%d %d", &N, &M);
    for (int a,b,c,i = 0; i < M; i++) {
        scanf("%d %d %d", &a, &b, &c);
        adj[a].push_back({b,c});
        if (c < 3) adj[b].push_back({a,c});
    }

    for (int i = 1; i <= N; i++) {
        accuses[0] = accuses[1] = 0;
        accuse_list[0].clear();
        accuse_list[1].clear();
        if (!scan_component(i, parity[i])) {
            printf("MISTAKE\n");
            return 0;
        }
        set<int> a(accuse_list[0].begin(), accuse_list[0].end());
        for (int j : accuse_list[1]) if (a.find(j) != a.end()) {
            printf("MISTAKE\n");
            return 0;
        }
        if (accuses[0] || accuses[1]) components.push_back({accuses[0],accuses[1]});
        if (accuses[0] && accuses[1]) both_sides_accuse = 1;
    }

    if (both_sides_accuse) {
        int a = 0, b = 0;
        for (auto i : components) {
            if (!i.first || !i.second) continue;
            if (!a) a = i.first, b = i.second;
            else {
                if (a != i.first && a != i.second) a = -1;
                if (b != i.first && b != i.second) b = -1;
            }
        }
        if (banned[a]) a = -1;
        if (banned[b]) b = -1;
        if (a < 0 && b < 0) printf("MISTAKE\n");
        else if (a < 0) printf("%d\n", b);
        else if (b < 0) printf("%d\n", a);
        else if (a < b) printf("%d\n%d\n", a, b);
        else printf("%d\n%d\n", b, a);
    } else {
        bool possible = 0;
        for (int i = 1; i <= N; i++) if (!banned[i]) printf("%d\n", i), possible = 1;
        if (!possible) printf("MISTAKE\n");
    }
}

