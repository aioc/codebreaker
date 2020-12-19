#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

int a[100005];
vector<int> bv;
int main(){
    // n = num of bins
    // b = balls
    // switched around cause wow was that confusing :/
    int n,balls;
    scanf("%d %d", &n, &balls);
    for (int i = 0; i < n; i++){
        scanf("%d", &a[i]);
        bv.push_back(a[i]);
    }
    sort(bv.begin(),bv.end());
    int minheight = 0;
    int pos = 0;
    int lv = 0;
    for (int i = 0; i < n; i++){
        int num = (n-i) * (bv[i]-lv);
        if (num >= balls){
            pos = (balls-1) % (n-i);
            minheight = lv;
            break;
        }
        balls -= num;

        lv = bv[i];
    }
    pos++;
    int cnt = 0;
    for (int i = 0; i < n; i++){
        if (a[i] >= minheight){
            cnt++;
        }
        if (cnt == pos){
            printf("%d\n", i+1);
            break;
        }

    }
}

