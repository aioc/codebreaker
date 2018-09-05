#include <cstdio>
#include <algorithm>

int n;
char a[32345], b[32345], c[32345];

int cache[32345][2];
bool seen[32345][2];
int dp(int i, int k) {
    if (i == n) return 0;
    if (seen[i][k]) return cache[i][k];
    seen[i][k] = 1;
    cache[i][k] = 1e9;
    if ((k?b:a)[i] == c[i]) {
        if ((k?b:a)[i+1] == c[i+1]) cache[i][k] = dp(i+1,k);
        else cache[i][k] = dp(i+1,k^1)+1;
    }
    return cache[i][k];
}

int main() {
    scanf("%d %s %s %s", &n, a, b, c);
    int k = std::min(dp(0,0),dp(0,1));
    if (k == 1e9) printf("PLAN FOILED\n");
    else {
        printf("SUCCESS\n");
        printf("%d\n", k);
    }
}


