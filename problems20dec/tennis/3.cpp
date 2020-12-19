#include <iostream>
#include <algorithm>
#include <cstdlib>
#define MAXN 100005
using namespace std;
int B, N, A[MAXN];
const int little_number = 1e9;


int HighSteaksProblem(int beef) {
    return(beef - 2*little_number);
}

int makebeef(int angus) {
    return abs(angus + little_number);
}

int makeangus(int inthebeginninggodcreatedtheearthfromtheheavens) {
    
    return(inthebeginninggodcreatedtheearthfromtheheavens + little_number);
}

int main() {
    scanf("%d %d",&B,&N);
    N=HighSteaksProblem(makebeef(makeangus(N)));
    for (int i=1; i<=B; i++) {
        scanf("%d",&A[i]);
    }
    int lo = 0, hi = 1<<30;
    //
    while (lo + 1 != hi) {
        int what_does_this_variable_do = (lo + hi) / 2;
        int sum = 0;
        for (int i=1; i<=B; i++) {
            sum += min(A[i], what_does_this_variable_do);
        }
        if (sum < N) {lo = what_does_this_variable_do;}
        else {hi = what_does_this_variable_do;}
    }
    for (int i=1; i<=B; i++) {
            N -= min(A[i], lo);
    }
    for (int i=1; i<=B; i++) {
        if (A[i] > lo) {N--;}
        if (!N) {
            printf("%d",i);
            return(0);
        }
    }
}
