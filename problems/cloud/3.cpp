#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int N, K;
vector<int> d;

int clamp(int x) {
    x = max(0, x);
    x = min(N-1, x);
    return x;
}

int local_search(int who) {
    int l = clamp(who-2*K);
    int r = clamp(who+2*K);
    int smallest_seen = 1e9;
    int cs = 0;
    for(int i = l; i < r; i++) {
        cs += d[i];
        if(i-K >= l) {
            cs -= d[i-K];
        }
        if(i-l+1 > K) { 
            smallest_seen = min(smallest_seen, cs);
        }
    }
    return smallest_seen;
}


int main() {
    cin >> N >> K;
    for(int i = 0; i < N-1; i++) {
        int x;
        cin >> x;
        d.push_back(x);
    }

    // The maximum size cloud is constrained by the pair
    // of people who stand closest together, so find the
    // smallest gap and do a local search around there.
    pair<int, int> smallest = {d[0], 0};
    for(int i = 0; i < N-1; i++) {
        smallest = min(smallest, {d[i], i});
    }
    cout << local_search(smallest.second) << "\n";
}
