#include <cstdio>
#include <utility>
#include <algorithm>
using namespace std;

typedef pair<int,int> pii;
#define mp make_pair
int p[3];
int c[3];
bool used[3];
int opt[3];
int main(){
    int d,c0;
    scanf("%d %d %d %d %d %d", &d,&c0,&p[1],&c[1],&p[2],&c[2]);
    int inflow = c0;
    int balance = 0;
    // I can't math bash, and simlating is too cheese. 
    // Time to simulate with easier math bash!
    for (int i = 1; i <= d; i++){
        for (int j = 1; j <= 2; j++){
            if (!used[j] && balance >= p[j]){
                // this is the amount of cookies this factory 
                // will give me by the time d days are over
                opt[j] = (d-i+1) * c[j] - p[j]; 
            }
            else{
                opt[j] = -1;
            }
        }
        pii to_buy = max(mp(opt[1],1), mp(opt[2],2));
        if (to_buy.first > 0){
            int j = to_buy.second;
            used[j] = true;
            balance -= p[j];
            inflow += c[j];
        }
        balance += inflow;
    }
    printf("%d\n", balance);
}
