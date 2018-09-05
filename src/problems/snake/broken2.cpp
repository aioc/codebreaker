#include <bits/stdc++.h>
using namespace std;

int M;

// move = 0 for left
// move = 1 for right
void print(int move) {
    printf("%c", move == 0 ? 'L' : 'R');
}

int dx[5] = {0, 1, 0, -1};
int dy[5] = {1, 0, 1, 0};

int X, Y, D;

int dist(int x, int y) {
    return abs(x-X) + abs(y-Y);
}

int main() {

    scanf("%d%d", &X, &Y);
    int x = 0, y = 0, d = 0, iter = 0;

    while (x != X || y != Y) {
        if(iter >= 10000) {
            printf("Somethinf is really wrong\n");
            break;
        }
        pair<int,int> closer = {1e9, 1e9};
        for(int dd = -1; dd <= 1; dd += 2) {
            int nd = (d + dd + 4)%4;
            int nx = x + dx[nd];
            int ny = y + dy[nd];
            int di = dist(nx, ny);
            // How does min work for pairs?
            // It first compares their first elements.
            // If they are the same, then it compares the second element.
            closer = min(closer, {di, nd});
        }
        printf("%c", (closer.second == ((d+3)%4) ? 'L' : 'R'));
        d = closer.second;
        x = x + dx[d];
        y = y + dy[d];
        iter++;
    }
    printf("\n");
}
