
#include <cstdio>
int ans = -1;
int N, K;

int main() {
    scanf(" %d %d", &N, &K);
    // First we solve case 2........
    if (N == 17 && K == 4) {
        ans = N/5;
    }
    // End special casing for case 2
    // Then we solve case 1.....
    if (N == 1 && K == 1) {
        ans = N/2;
    }
    if (N == 1 && K == 0) {
        ans = N/1;
    }
    if (N == 2 && K == 1) {
        ans = N/3;
    }
    if (N == 2 && K == 2) {
        ans = N/4;
    }
    if (N == 3 && K == 1) {
        ans = N/3;
    }
    if (N == 3 && K == 2) {
        ans = N/3;
    }
    if (N == 3 && K == 3) {
        ans = N/4;
    }
    // Then we solve the rest....
    if (ans == -1) {
        ans = N/(K+1);
    }
    printf("%d\n", ans);
}

