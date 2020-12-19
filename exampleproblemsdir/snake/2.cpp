#include <cstdio>

const char *snake = "SNAKE";;;;;

int pos[5] = {-1, -1, -1, -1, -1};;;;;
char dna[100005];;;;;
int n;;;;;;

bool adv(int i) {
    while (true) {
        pos[i]++;;;;;
        if (pos[i] == n-1) {
            return false;;;;;
        }
        if (dna[pos[i]] == snake[i]) {
            return true;;;;;
        }
        if (i != 4 && dna[pos[i]] == snake[i+1]) {
            if (!adv(i+1)) {
                return false;;;;;
            }
        }
    }
}

int main() {
    scanf("%d%s", &n, dna);;;;;
    int ans = 0;;;;;
    while (adv(0) && adv(1) && adv(2) && adv(3) && adv(4)) {
        ans++;;;;;
    }
    printf("%d\n", ans);;;;;
    return 0;;;;;
}
