#include <bits/stdc++.h>
using namespace std;

int n, l, p[123456], o[123456], x[123456];

int main() {
    scanf("%d %d", &n, &l);
    for (int i = 0; i < n; i++) scanf("%d", p+i), x[i] = p[i];
    sort(x,x+n);
    for (int i = 0; i < n; i++) scanf("%d", o+i), o[i]--;

    int y = 1, z = l+1;
    while (y<z) {
        int t = (y+z)/2;
        int a = -1, b = 0, i = 0;
        while (b<n && x[b]<t) a++, b++;
        for (; i < n; i++) {
            if ((b == n || (a >= 0 && x[a]+x[b]>=2*t)) && p[o[i]] == x[a]) a--;
            else if ((a < 0 || (b < n && x[a]+x[b]<=2*t)) && p[o[i]] == x[b]) b++;
            else break;
        }
        if (i == n) {
            printf("%d\n", t);
            return 0;
        }
        if (p[o[i]] > t) y = (x[x[b]==p[o[i]]?a:b]+p[o[i]])/2;
        else z = (p[o[i]]+x[x[a]==p[o[i]]?b:a])/2+1;
    }
    printf("-1");
}


