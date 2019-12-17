// No comment
#include <iostream>
#include <algorithm>

using namespace std;

char makeBeef(char x) {
    string snake = "SNAKE";
    string cow = "ANGUS";
    for(int i = 0; i < 5; i++) {
        if(snake[i] == x) {
            return cow[i];
        }
    }
    return 'X';
}

int N;
string S;

const int FAIL = -1234;
int _K;
int f(char thing, int start) {
    if(start == FAIL || _K == 0) {
        return FAIL;
    }
    int k = _K;
    for(int i = start; i < N; i++) {
        if(S[i] == thing) {
            k--;
        }
        if(k == 0) {
            return i;
        }
    }
    return FAIL;
}

const int NO_SOLN = 0;

int main() {
    cin >> N >> S;
    transform(begin(S), end(S), begin(S), makeBeef);

    int best = NO_SOLN;

    int l = 0;
    int r = N;
    while(l <= r) {
        _K = (l+r)/2;
        if(f('S', f('U', f('G', f('N', f('A', 0))))) == FAIL) {
            r = _K-1;
        } else {
            l = _K+1;
            best = best < _K ? _K : best;
        }
    }
    cout << best << "\n";
    return 0;
}
