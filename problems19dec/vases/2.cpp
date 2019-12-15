#include <iostream>
#include <vector>

using namespace std;

int N;

// Apparently you could do vector<int>(3, 0); to prefill the vector.
vector<int> v;

bool invalid() {
    bool ok = true;
    ok &= v[0] + v[1] + v[2] == N;
    for(int i = 0; i < 3; i++) {
        ok &= v[i] > 0 && v[i] < N;
        ok &= v[i] != v[(i+1)%3];
    }
    return !ok;
}

int main() {
    v.push_back(0);
    v.push_back(0);
    v.push_back(0);
    cin >> N;

    // Evenly spread them out
    for(int i = 0; i < N; i++) {
        v[i%3] += 1;
    }

    // Fiddle with it if it's broken
    if(v[0] == v[1]) {
        v[0] += 1;
        v[1] -= 1;
    }
    if(v[1] == v[2]) {
        v[1] += 3;
        v[2] -= 3;
    }
    if(v[2] == v[0]) {
        v[2] += 7;
        v[0] -= 7;
    }

    if(invalid()) {
        cout << "-1 -1 -1\n";
    } else {
        cout << v[0] << " " << v[1] << " " << v[2] << "\n";
    }
}
