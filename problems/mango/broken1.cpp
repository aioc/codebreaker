#include<iostream>
using namespace std;
const int MAXN = 1000, di[] = {-1, 1, -1, 1}, dd[]= {1,1, -1, -1};

int main(){
    int ix, cx, id, cd, ans;
    cin >> ix >> cx >> id >> cd;
    for (int pos = 0; pos < MAXN; pos++){
        for (int d = 0; d < 4; d++){
            if (pos == ix + di[d]*id && pos == cx + dd[d]*cd){
                ans=pos;
            }
        }
    }
    cout << ans<< endl;
}
