#include <iostream>
using namespace std;

const int MAX_R = 10+5;
const int MAX_C = 1e5 + 5;
int R, C, Q;

int grid[MAX_R][MAX_C];

int dr[4] = {0,  0, -1, 1};
int dc[4] = {1, -1,  0, 0};
bool isPeak(int r, int c) {
    if(r < 2 || c < 2 || r > R+1 || c > C+1) {
        return false;
    }
    for(int d = 0; d < 4; d++) {
        int nr = r + dr[d];
        int nc = c + dc[d];
        if(grid[nr][nc] > grid[r][c]) {
            return false;
        }
    }
    return true;
}

int adjPeaks(int r, int c) {
    int peaks = 0;
    for(int d = 0; d < 4; d++) {
        // true cast to an int is 1.
        peaks += isPeak(r + dr[d], c + dc[d]);
    }
    peaks += isPeak(r, c);
    return peaks;
}

int main() {
    cin >> R >> C >> Q;
    if(R == 1 && C == 1) {
        for(int q = 0; q < Q+1; q++) {
            cout << "1\n";
        }
        return 0;
    }
    // Offset indexing by 1, to have
    // a 2 element wide buffer around the array
    for(int r = 2; r <= R+1; r++) {
        for(int c = 2; c <= C+1; c++) {
            cin >> grid[r][c];
        }
    }

    int peaks = 0;
    // Initial count
    for(int r = 2; r <= R+1; r++) {
        for(int c = 2; c <= C+1; c++) {
            if(isPeak(r, c)) {
                peaks++;
            }
        }
    }
    cout << peaks << "\n";

    for(int q = 2; q <= Q+1; q++) {
        int r, c, x;
        cin >> r >> c >> x;
        r++; c++; x++;

        int preAdj = adjPeaks(r, c);
        grid[r][c] = x;
        int postAdj = adjPeaks(r, c);
        peaks += postAdj - preAdj;
        cout << peaks << "\n";
    }
    return 0;
}
