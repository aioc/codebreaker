#include <bits/stdc++.h>
using namespace std;

const int WHITE = 0;
const int BLACK = 1;
const int MAX_N = 100005;

int N, E;
vector<int> edges[MAX_N];
bool seen[MAX_N];
int colour[MAX_N];

int amoWhite, amoBlack;

int upto;

void dfs(int cur, int col);

int main() {
    scanf("%d %d",&N, &E);

    for (int i=0;i<E;i++) {
        int a, b;
        scanf("%d %d",&a,&b);
        edges[a].push_back(b);
        edges[b].push_back(a);
    }

    int total = 0;
    for (int i=1;i<=N;i++) {
        if (!seen[i]) {
            // First, work out the initial colour
            // In general, its good to choose
            // the colour that was used most in the
            // previous run
            int toColor = WHITE;
            if (amoBlack > amoWhite) {
                toColor = BLACK;
            }
            amoBlack = 0;
            amoWhite = 0;
            dfs(i, toColor);
            if (amoWhite > amoBlack) {
                total += amoWhite;
            } else {
                total += amoBlack;
            }
        }
    }
    printf("%d\n", total);
    return 0;
}

void dfs(int cur, int col) {
    if (seen[cur]) {
        return;
    }
    seen[cur] = true;
    if (col == WHITE) {
        amoWhite++;
    } else {
        amoBlack++;
    }
    for (auto o: edges[cur]) {
        if (seen[o]) {
            // Better check to see if its the right colour
            // Else odd cycle! (Silly judges)
            if (colour[o] == col) {
                printf ("Impossib1e\n");
                exit(0);
            }
        } else {
            colour[o] = 1 - col;
            dfs(o, 1 - col);
        }
    }
}
