#include <bits/stdc++.h>

using namespace std;

int a[100000];
int cnt[100000];
int n;

void smart_sort() {
    for (int i = 0; i < n; i++) {
        cnt[a[i]]++;
    }
    int j = 0;
    for (int i = 1; i <= n; i++) {
        while (cnt[i]) {
            a[j++] = i;
            cnt[i]--;
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) scanf("%d", &a[i]);

    // only sheep trust the stl sort
    smart_sort();

    int i = 0;
    while (i < n) {
        if (i+a[i] > n || a[i+a[i]-1] != a[i]) {
            puts("NO");
            return 0;
        }
        i += a[i];
    }
    puts("YES");
}
