#include <cstdio>

using namespace std;

int a, b, c;

void fail() {
    a = -1;
    b = -1;
    c = -1;
}

int main() {
    int N;
    scanf("%d", &N);
    a = N/2;
    b = N/3;

    // Kevin said this would help
    // If N is odd, jiggle a
    if(N%2 == 1) { 
        a++;
    }

    // Laeeque said this would help
    // If N is a multiple of 8, jiggle b
    if(N%8 == 0) {
        b++;
    }
    c = N - a - b;

    if(a < 0 || b < 0 || c < 0) {
        fail(); 
    }
    if(a + b + c != N) {
        fail();
    }
    if(a == b || b == c || c == a) {
        fail();
    }

    printf("%d %d %d", a, b, c);
    return 0;
}
