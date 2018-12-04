#include <bits/stdc++.h>

#define fo(i,a,b) for (int i = a; i < b; i++)
#define sz(v) int(v.size())

using namespace std;

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    vector<int> p(n-1);
    fo(i,0,n-1) {
        scanf("%d", &p[i]);
        if (i) p[i] += p[i-1];
    }
    int res = 1e9;
    fo(i,0,n-k-1) res = min(res, p[i+k]-p[i]);
    printf("%d\n", res);
}

