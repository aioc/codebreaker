#include <cstdio>
#include <algorithm>
using namespace std;
int d,c0;
int p1,c1;
int p2,c2;

// What the heck this literally fails one one case on oracc nooooo :<

int best(){
    // just buy 1
    int ret = 0;
    int cur = 0;
    int income = c0;
    bool bought1 = false;
    for (int t = 0; t < d; t++){
        if (cur >= p1 && !bought1){
            bought1 = true;
            income += c1;
            cur -= p1;
        }
        cur += income;
    }
    ret = cur;

    // buy 1 then 2
    cur = 0;
    income = c0;
    bought1 = false;
    bool bought2 = false;
    for (int t = 0; t < d; t++){
        if (!bought1){
            if (cur >= p1 ){
                bought1 = true;
                income += c1;
                cur -= p1;
            }
        }
        else if (bought1 && !bought2 && cur >= p2){
            bought2 = true;
            income += c2;
            cur -= p2;
        }
        cur += income;
    }
    return max(ret,cur);
}

int main(){
    // freopen("cookiesin.txt", "r", stdin);
    // freopen("cookiesout.txt", "w", stdout);

    
    scanf("%d %d %d %d %d %d", &d, &c0, &p1, &c1, &p2, &c2);
    // buy no factories
    int ans = d * c0;
    
    ans = max(ans,best());
    swap(p1,p2);
    swap(c2,c1);
    printf("%d\n", max(ans,best()));
}
