#include <bits/stdc++.h>

// move = 0 for left
// move = 1 for right
void print(int move) {
    printf("%c", move == 0 ? 'L' : 'R');
}

int main() {
    //freopen("snakein.txt", "r", stdin);
    //freopen("snakeout.txt", "w", stdout);
    // d = direction = {0,1,2,3} for n,e,s,w respectively
    int x = 0, y = 0, d = 0;
    int endx, endy;

    scanf("%d%d", &endx, &endy);

    while (true) {
        if (x == endx && y == endy) break;

        // move horizontally
        {
            assert(d == 0 || d == 2);
            int move, nextd;
            if (x < endx) {
                x++;
                nextd = 1;
                if (d == 0) move = 1;
                else move = 0;
            } else {
                x--;
                nextd = 3;
                if (d == 0) move = 0;
                else move = 1;
            }

            print(move);
            d = nextd;
        }

        if (x == endx && y == endy) break;

        // move vertically
        {
            assert(d == 1 || d == 3);
            int move, nextd;
            if (y < endy) {
                y++;
                nextd = 0;
                if (d == 1) move = 0;
                else move = 1;
            } else {
                y--;
                nextd = 2;
                if (d == 1) move = 1;
                else move = 0;
            }

            print(move);
            d = nextd;
        }

    }
    printf("\n");
}

