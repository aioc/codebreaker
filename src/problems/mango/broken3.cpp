// Skrrrrr POP POP
#include <iostream>
#include <vector>

using namespace std;

int A, B, C, D;

vector<int> pos;

bool good(int x) {
    int cnt = 0;
    for(auto y: pos) {
        if(y == x) {
            cnt++;
        }
    }
    return cnt == 2 || cnt == 3;
}

int main() {
    cin >> A >> B >> C >> D;
    pos.push_back(A+C);
    pos.push_back(A-C);
    pos.push_back(B+D);
    pos.push_back(B-D);
    for(int i = min(A-C, B-D); i <= max(A+C, B+D); i++) {
        if(good(i)) {
            cout << i << "\n";
            return 0;
        }
    }
    cout << "Man's not hot\n";
    return 0;
}
