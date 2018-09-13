#include<iostream>
#include<algorithm>
#include<map>
#include<utility>
using namespace std;

const int MAXN = 100005;

struct Platform {
    int h, l, r, c;

    bool operator< (const Platform &other) const {
        // (bug) I forgot to sort in increasing order
        return h > other.h;
    }
};

Platform plats[MAXN];
int N;
map<int,int> v; // stores map of <falling pos, value>

int main(){
    cin >> N;
    for (int i = 0; i < N; i++){
        cin >> plats[i].h >> plats[i].l >> plats[i].r >> plats[i].c;
    }

    sort(plats, plats+N);

    v[plats[0].l-1] = v[plats[0].r+1] = plats[0].c;
    for (int i = 1; i < N; i++){
        // find max value in covered range, if nothing discard and continue
        auto it = v.lower_bound(plats[i].l); // first item that is not less than l
        int bestval = -1;

        // (bug) I Forgot to put the end check in
        while (it != v.end() && it->first <= plats[i].r) {
            bestval = max(bestval, it->second);
            it = v.erase(it);
        }

        if (bestval == -1) continue;
        bestval += plats[i].c;
        // set new values, possibly increasing values

        // (bug) I Forgot to put the second one of these lines in
        v[plats[i].l-1] = max(bestval, v.count(plats[i].l-1) == 0 ? 0 : v[plats[i].l-1]);
        v[plats[i].r+1] = max(bestval, v.count(plats[i].r+1) == 0 ? 0 : v[plats[i].r+1]);
    }

    int bestval = 1;
    for (auto a: v) bestval = max(bestval, a.second);

    cout << bestval << endl;
}
