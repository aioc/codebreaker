#include <bits/stdc++.h>

#define sz(z) (int)z.size()
#define fo(i,a,b) for (auto (i) = (a); (i) < (b); (i)++)
#define mp make_pair
#define pb push_back

using namespace std;

#define DEBUG

#ifdef DEBUG
#define D(x...) fprintf(stderr,x)
#else
#define D(x...) 
#endif

typedef long long ll;
typedef pair<int,int> ii;

int H[12345];
int V[12345];
int dp[3005][3005];
int preV[3005][3005];
int preH[3005][3005];

int main() {
    int r, c, k, h, v;
    scanf("%d %d %d %d %d", &r, &c, &k, &h, &v);
    fo(i,0,h) {
        scanf("%d", &H[i]);
    }
    sort(H,H+h);
    H[h++] = r;
    fo(i,0,v) {
        scanf("%d", &V[i]);
    }
    sort(V,V+v);
    V[v++] = c;
    // long longs to binary search the answer    
    // in case the answer is very big
    ll lo = 0;
    ll hi = (1LL<<31);
    while (lo < hi) {
        int mi = lo + hi >> 1;
        int bad = 0;
        if (bad) continue;

        fo(i,0,h) {
            int k = 0;
            fo(j,0,v) {
                while (k < j && H[i] * (V[j] - V[k]) > mi) k++;
                preV[i][j] = k;
            }
        }

        fo(j,0,v) {
            int k = 0;
            fo(i,0,h) {
                while (k < i && V[j] * (H[i] - H[k]) > mi) k++;
                preH[i][j] = k;
            }
        }
        fo(i,0,h) fo(j,0,v) {
            if (H[i] * V[j] < mi) dp[i][j] = 0;
            else {
                dp[i][j] = 123123123;
                int nx = preH[i][j];
                if (nx != i) {
                    dp[i][j] = min(dp[i][j], 1 + dp[preH[i][j]][j]);
                }
                int ny = preV[i][j];
                if (ny != j) {
                    dp[i][j] = min(dp[i][j], 1 + dp[i][preV[i][j]]);
                }
            }
        }
        if (dp[h-1][v-1] <= k) {
            hi = mi;
        } else {
            lo = mi+1;
        }
    }
    printf("%d\n", lo);
    return 0;
}
