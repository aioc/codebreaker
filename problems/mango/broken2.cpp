#include <iostream>

using namespace std;

int ishraqPosition;
int ishraqRadius;
int clementPosition;
int clementRadius;

int main() {
    cin >> clementPosition >> ishraqPosition >> clementRadius >> ishraqRadius;

    if(ishraqPosition - ishraqRadius == clementPosition - clementRadius) {
        cout << ishraqPosition - ishraqRadius << "\n";
    }
    else if(ishraqPosition + ishraqRadius == clementPosition - clementRadius) {
        cout << ishraqPosition + ishraqRadius << "\n";
    }

    if(ishraqPosition - ishraqRadius == clementPosition + clementRadius) {
        cout << ishraqPosition - ishraqRadius << "\n";
    }
    else if(ishraqPosition + ishraqRadius == clementPosition + clementRadius) {
        cout << ishraqPosition + ishraqRadius << "\n";
    }
}
