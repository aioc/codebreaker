// Chimera -- limitd memory streaming algorithm
// Often in computing it's not possible to store all your input
// in memory, since it could be quite large. Although that isn't the case here,
// it is possible to solve this problem in the following constrained way:
// Given only access to the functions nextA, nextB and nextC for the three strings A B and C,
// the problem can be solved in constant memory and still in linear time.
// Allow me to demonstrate:
#include <iostream>
using namespace std;

string _A, _B, _C;
int _N;

int iterA, iterB, iterC;

char nextA() {
    if(iterA != _N) {
        return _A[iterA++];
    } else {
        return '?';
    }
}

char nextB() {
    if(iterB != _N) {
        return _B[iterB++];
    } else {
        return '?';
    }
}

char nextC() {
    if(iterC != _N) {
        return _C[iterC++];
    } else {
        return '?';
    }
}


int streamingSolve(int N) {
    // Find the longest matching prefix
    char a, b, c;
    a = nextA();
    b = nextB();
    c = nextC();
    N--;
    while(a == b && b == c) {
        a = nextA();
        b = nextB();
        c = nextC();
        N--;
    }
    // Alternate between the two sequences
    int ans = 0;
    bool onA = (a == c);
    while(N > 0) {
        a = nextA();
        b = nextB();
        c = nextC();
        N--;
        // Fail if no match
        if(a != c && b != c) {
            return -1;
        }
        if(onA) {
            if(a != c) {
                ans++;
                onA = !onA;
            }
        } else {
            if(b != c) {
                ans++;
                onA = !onA;
            }
        }
    }
    return ans;
}

int main() {
    cin >> _N;
    cin >> _A >> _B >> _C;
    int ans = streamingSolve(_N);
    if(ans == -1) {
        cout << "PLAN FOILED\n";
    } else {
        cout << "SUCCESS\n";
        cout << ans << "\n";
    }
    return 0;
}



