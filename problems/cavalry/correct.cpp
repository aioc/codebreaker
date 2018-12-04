#include <bits/stdc++.h>
using namespace std;

int n, a[100005];

int main() {
    freopen("cavalryin.txt", "r", stdin);
    freopen("cavalryout.txt", "w", stdout);
    scanf("%d", &n);
    for (int i = 0, x; i < n; i++) scanf("%d", &x), a[x]++;
    for (int i = 1; i <= 100000; i++) if (a[i] % i) {
        printf("NO\n");
        return 0;
    }
    printf("YES\n");
}
