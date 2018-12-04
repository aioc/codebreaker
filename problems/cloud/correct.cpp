#include <bits/stdc++.h>
using namespace std;

int N, K, a[100005], ans = 2e9;

int main() {
    freopen("cloudin.txt", "r", stdin);
    freopen("cloudout.txt", "w", stdout);
    scanf("%d %d", &N, &K);
    for (int i = 1; i < N; i++) scanf("%d", a+i), a[i] += a[i-1];
    for (int i = 0; i+K < N; i++) ans = min(ans, a[i+K]-a[i]);
    printf("%d\n", ans);
}

