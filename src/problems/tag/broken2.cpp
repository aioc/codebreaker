// We can reuse or solution to spies for Tag right?
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int MAX = 123456;

int root[MAX];

void uf_init(int n) {
    for(int i = 1; i <= n; i++) {
        root[i] = i;
    }
}

int uf_root(int x) {
    if(root[x] == x) {
        return x;
    } else {
        root[x] = uf_root(root[x]);
        return root[x];
    }
}

void uf_join(int a, int b) {
    int rootA = root[a];
    int rootB = root[b];
    root[rootA] = rootB;
}

struct commlink {
    int a, b, c;
    // Used so that sort() knows to put small edges first
    // But this is not needed for Tag
    // const bool operator<(const commlink& oth) const {
    //    return c < oth.c;
    //}
};

vector<commlink> links;

int kruskals(vector<commlink> l, int max_edges) {
    int minWeight = 0;
    // Sort no longer needed for Tag
    //sort(l.begin(), l.end());
    for(auto edge: l) {
        // Always merge, since the thing is already a tree anyway in Tag
        //if(uf_root(edge.a) != uf_root(edge.b)) {
            max_edges--;
            minWeight += edge.c;
            uf_join(edge.a, edge.b);
            if(max_edges == 0) {
                break;
            }
        //}
    }
    return minWeight;
}

int main() {
    
    int N, M, K;

    cin >> N >> M; //>> K;
    for(int i = 1; i <= M; i++) {
        commlink c;
        cin >> c.a >> c.b; // >> c.c;
        c.c = 1;
        links.push_back(c);
    }
    
    uf_init(N);
    int mstCost = kruskals(links, N-2); //K);
    //cout << mstCost << "\n";
    
    int red = 0;
    int blue = 0;
    for(int i = 1; i <= N; i++) {
        if(uf_root(i) == uf_root(1)) {
            red++;
        } else if(uf_root(i) == uf_root(2)) {
            blue++;
        }
    }
    cout << red << " " << blue << "\n";
    return 0;
}
