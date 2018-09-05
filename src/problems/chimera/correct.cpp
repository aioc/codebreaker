#include <bits/stdc++.h>

#define FAIL_STRING "PLAN FOILED"
#define SUCCESS_STRING "SUCCESS"

const int maxn = 300*1000+5;

int n;
char a[maxn], b[maxn], c[maxn];

int main() {
    scanf("%d %s %s %s", &n, a, b, c);

    assert(n <= maxn);
    assert((int)strlen(a) == n);
    assert((int)strlen(b) == n);
    assert((int)strlen(c) == n);

    int ans = 0;
    bool aok = true, bok = true;
    for (int i = 0; i < n; i++) {
        if (a[i] != c[i] && b[i] != c[i]) {
            printf(FAIL_STRING "\n");
            return 0;
        }
        if (a[i] != c[i]) aok = false;
        if (b[i] != c[i]) bok = false;
        if (!aok && !bok) {
            ans++;
            if (a[i] == c[i]) aok = true;
            if (b[i] == c[i]) bok = true;
        }
    }
    printf(SUCCESS_STRING "\n");
    printf("%d\n", ans);
}

