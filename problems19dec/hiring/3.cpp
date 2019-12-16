/////////////////////
// 1 2 1 3 1 2 1 4 //
/////////////////////
#include <bits/stdc++.h>
using namespace std;

int N, S, M, x[100005], s[100005], m[100005];
int ans;

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        // I love hacky pointer arithmetic :)
        scanf("%d", x+i);
    }

    scanf("%d", &S);
    for (int i = 0; i < S; i++) {
        scanf("%d", s+i);
    }

    // 1 2 1 3 1 2 1 5 1 2 1 3

    scanf("%d", &M);
    for (int i = 0; i < M; i++) {
        scanf("%d", m+i);
    }

    sort(x, x+N, greater<int>());
    sort(s, s+S);
    sort(m, m+N, greater<int>());

    // 1 2 1 4 1 2 1 3 1 2

    for (int i = 0; i < S; i++) {
        if (N >= 1 && x[N-1] <= s[i]) {
            ans += 1;
            N--;
        }
    }

    reverse(x, x+N);
    for (int i = 0; i < M; i++) {
        if (N >= 1 && x[N-1] >= m[i]) {
            ans += 1;
            N--;
        }
    }

    // 1 6 1 2 1 3 1 2 1

    printf("%d\n", ans);

    return 0;
}

// 4 1 2 1 3 1 2 1 5
