#include <bits/stdc++.h>

int main() {
    //freopen("manin.txt", "r", stdin);
    //freopen("manout.txt", "w", stdout);
    int a, b, da, db;
    scanf("%d%d%d%d", &a, &b, &da, &db);
    int ans = a - da;
    if (std::abs(ans - b) != db) ans = a + da;
    printf("%d\n", ans);
}

