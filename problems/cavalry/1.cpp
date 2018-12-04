#include <bits/stdc++.h>

using namespace std;

int n;
int a[1000005];

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) scanf("%d", &a[i]);

    int first_unused = 0;
    for (int i = 0; i < n; i++) if (a[i] != 0) {
        int x = a[i];
        int c = a[i];
        for (int j = first_unused; j < n && c != 0; j++) {
            if (a[j] == x) {
                c--;
                a[j] = 0;
                if (j == first_unused) first_unused++;
            }
        }
        if (c != 0) {
            puts("NO");
            return 0;
        }
    }

    puts("YES");
    return 0;
}
