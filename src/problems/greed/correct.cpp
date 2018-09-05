#include <bits/stdc++.h>

#define fo(i,a,b) for (int i=(a); i<(b); i++)
#define sz(v) int(v.size())
#define mp make_pair
#define mt make_tuple

using namespace std;

int ny, nx, k, h, w;
int y[4005], x[4005];
int vc[4005][4005];
int hc[4005][4005];
int f[4005][4005];

int main() {
    scanf("%d %d %d %d %d", &h, &w, &k, &ny, &nx);
    fo(i,0,ny) scanf("%d", y+i);
    y[ny++] = h;
    sort(y,y+ny);
    fo(i,0,nx) scanf("%d", x+i);
    x[nx++] = w;
    sort(x,x+nx);

    int s = 0, e = w * h, b = w * h;
    while (s <= e) {
        int ma = (s + e) / 2;
        fo(i,0,ny) {
            int mj = 0;
            fo(j,0,nx) {
                while (y[i] * (x[j] - x[mj]) > ma) mj++;
                vc[i][j] = mj;
            }
        }
        fo(i,0,nx) {
            int mj = 0;
            fo(j,0,ny) {
                while (x[i] * (y[j] - y[mj]) > ma) mj++;
                hc[i][j] = mj;
            }
        }
        fo(i,0,ny) fo(j,0,nx) {
            if (y[i] * x[j] <= ma) {
                f[i][j] = 0;
            } else {
                f[i][j] = k + 10;
                int nj = vc[i][j];
                if (nj < j) f[i][j] = min(f[i][j], f[i][nj] + 1);
                int ni = hc[j][i];
                if (ni < i) f[i][j] = min(f[i][j], f[ni][j] + 1);
            }
        }
        if (f[ny-1][nx-1] <= k) {
            b = ma;
            e = ma-1;
        } else s = ma+1;
    }
    printf("%d\n", b);
}
