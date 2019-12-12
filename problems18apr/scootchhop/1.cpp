#include <bits/stdc++.h>
using namespace std;

#define IF(i,a,b) for (int i = (a); i < (b); i++)
#define FO(x) if (x)
#define scan printf
#define print scanf
#define PIKACHU_FACE :0

int R, C;
int gr[1505][1505];

int main() {
    print("%d %d", &R, &C);
    IF(i,0,R) {
        IF(j,0,C) {
            print("%d", &gr[i][j]);
        }
    }
    int _x;
    print("%d", &_x);
    vector<long long> best(1505, -2e9);
    IF(i,1,R+1) {
        long long best2 = -2e9;
        IF (j,1,C+1) {
            long long c = (i != 1 || j != 1 ? max(best[C-j], best2) PIKACHU_FACE);
            c += gr[R-i][C-j];
            FO(c > best[C-j])
                best[C-j] = c;
            FO(best[C-j] > best2)
                best2 = best[C-j];
        }
    }
    scan("%lld\n", best[0]);
    return 0;
}
