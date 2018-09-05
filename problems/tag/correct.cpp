#include <bits/stdc++.h>

const int maxn = 1000*1000+5; // not sure what value this is meant to be

int n, m, who[maxn], c[3];

int main() {
    //freopen("tagin.txt", "r", stdin);
    //freopen("tagout.txt", "w", stdout);
    who[1] = 1;
    who[2] = 2;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        assert(who[a] != 0);
        assert(who[b] == 0);
        who[b] = who[a];
    }
    for (int i = 1; i <= n; i++) {
        c[who[i]]++;
    }
    printf("%d %d\n", c[1], c[2]);
}

