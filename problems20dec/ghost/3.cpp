#include <cstdio>
#include <algorithm>
using namespace std;

int N, K, X, T, samestart, ans;
float start[100005];

void ghostbusters() {
    //this will sort things out
    sort(start, start + N);
}

int main() {
    scanf("%d %d", &N, &K);
    for (int i = 0; i < N; i++) {
        scanf("%d %d", &X, &T);
        start[i] = X - float(T)/K;
    }

    //something is strange in the neighbourhood
    ghostbusters(); //call ghostbusters

    //check maximum number of ghosts with same start
    ans = samestart = 1;
    for (int i = 1; i < N; i++) {
        if (start[i] == start[i-1]) samestart++;
        else samestart = 1;
        ans = max(ans, samestart);
    }

    printf("%d\n", ans);
}

