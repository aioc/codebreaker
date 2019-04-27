#include <iostream>
using namespace std;

int g[450][450];
bool seen[3005][3005];
int cache[3005][3005];
int R, C;
const int INF = 1e9;

int dp(int rAt, int cAt) {
    if(rAt == R && cAt == C) {
        return 0;
    }
    if(!seen[rAt][cAt]) {
        seen[rAt][cAt] = true;
        int ans = -INF;
        
        // Drop to next row
        if(rAt != R) {
            ans = max(ans, dp(rAt+1, cAt) + max(0, g[rAt+1][cAt]));
        }
        
        // Or move in this row
        for(int c = cAt+1; c <= C; c++) {
            ans = max(ans, dp(rAt, c) + max(0, g[rAt][c]));
        }

        cache[rAt][cAt] = ans;
    }
    return cache[rAt][cAt];
}

int main() {
    cin >> R >> C;
    for(int r = 1; r <= R; r++) {
        for(int c = 1; c <= C; c++) {
            cin >> g[r][c];
        }
    }
    int ans = dp(1, 1) + g[1][1] + g[R][C];
    cout << ans << "\n";
}
