#include <iostream>
#include <vector>

using namespace std;

vector<int> a;
int BINS, BALLS;

long long trunc_sum(int ceiling) {
    long long sum = 0;
    for(auto x: a) {
        sum += min(x, ceiling);
    }
    return sum;
}

int main() {
    cin >> BINS >> BALLS;
    for(int i = 0; i < BINS; i++) {
        int x;
        cin >> x;
        a.push_back(x);
    }

    // Handle Sub2, because naive is good enough
    if(BALLS <= 100000) {
        int at = 0;
        while(1) {
            if(a[at]) {
                BALLS--;
                a[at]--;
                if(BALLS == 0) {
                    cout << at+1 << "\n";
                    return 0;
                }
            }
            at++;
            at %= BINS;
        }
    }

    // Binary search for the stopping height
    int l = 1;
    int r = 1e9;
    // Inclusive-inclusive
    while(l != r) {
        int m = (l+r)/2;
        long long sum = trunc_sum(m);
        // Balls do not fit at this height
        if(sum < BALLS) {
            l = m+1;
        } else {
            // They do fit, so possible candidate
            r = m;
        }
    }

    // Every bin is filled to height l-1, and some are filled to l
    int fill_height = l-1;
    BALLS -= trunc_sum(fill_height);
    for(int i = 0; i < BINS; i++) {
        if(a[i] > fill_height) {
            BALLS--;
            if(BALLS == 0) {
                cout << i+1 << "\n";
                return 0;
            }
        }
    }
    cout << "The tutors would like to have a word with you...\n";
}

