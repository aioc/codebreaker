#include <cstdio>
#include <algorithm>
using namespace std;

long long pos[100005];
long long pfx[100005];
long long sfx[100005];
int main(){
    int n,k,q;
    scanf("%d %d %d", &n,&k,&q);
    for (int i = 1; i <= n; i++){
        scanf("%lld", &pos[i]);
    }
    pfx[0] = 1e10+7;
    sfx[n+1] = 1e10+7;

    // let L[i] represent travelling from lady bug i to meet k ladybugs on the right
    // L[i] is also shifted by -pos[i] to account for the distance to travel to position i from the right
    // pfx[i] is thus the min among all L[j]'s where j is in the interval [1,i]

    for (int i = 1; i <= n-k+1; i++){
        pfx[i] = min(pfx[i-1], pos[i+k-1] - pos[i] - pos[i]);
    }
    for (int i = n-k+2; i <= n; i++){
        pfx[i] = pfx[i-1];
    }
    // R[i] is defined travelling from ladybug i to the left
    // sfx is min among all R[j]'s for j in [i,n]
    for (int i  = n; i >= k; i--){
        sfx[i] = min(sfx[i+1], pos[i] - pos[i-k+1] + pos[i]);
    }
    for (int i = k-1; i >= 1; i--){
        sfx[i] = sfx[i+1];
    }

    for (int i = 1; i <= q; i++){
        long long x;
        scanf("%lld", &x);

        long long ans = 0;
        int lo = 1;
        int hi = n;
        int best = 1;
        while (lo <= hi){
            int mid = (lo + hi)/2;
            if (x <= pos[mid]){
                best = mid;
                hi = mid-1;
            }
            else{
                lo = mid+1;
            }
        }
        // best is now the leftmost ladybug with pos >= x
        int left = pos[best] == x ? best : best-1;
        int right = best;
        // l choice is the min dist to travel to a ladybug on the left, then see k ladybugs on the right
        // r choice is the min dist to travel to a ladybug on the right, then see k ladybugs on the left
        long long lchoice = pfx[left] + x;
        long long rchoice = sfx[right] - x;
        ans = min(lchoice,rchoice);

        // also try going directly to the left or right
        if (pos[best] != x){
            if (right + k-1 <= n){
                ans = min(ans,pos[right+k-1]-x);
            }
            if (left - k + 1 >= 1){
                ans = min(ans,x-pos[left-k+1]);
            }
        }
        printf("%lld ", ans);   
    }
}
