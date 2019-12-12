#include <cstdio>

using namespace std;

int main() {
    int N;
    scanf("%d", &N);
    
    if(N <= 5) {
        printf("%d %d %d\n", -1, -1, -1);
    } else {
        printf("%d %d %d\n", 1, 2, N-3);
    }
}
