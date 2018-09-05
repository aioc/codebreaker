#include <iostream>
#include <vector>
using namespace std;

int N, M;

int colour[123456];

int main() {
    scanf("%d %d\n", &N, &M);
    colour[2-1] = 1;
    for(int i = 0; i < M; i++) {
        int a, b;
        scanf("%d %d",  &a, &b);
        // Make the problem go from 0 to N-1 instead of 1 to N
        a--; b--;
        colour[b] = colour[a];
    }
    int b = 0;
    int r = 0;
    for(int i = 1; i < N; i++) {
        if(colour[i]) {
            b++;
        } else {
            r++;
        }
    }
    printf("%d %d\n", r, b);
}
