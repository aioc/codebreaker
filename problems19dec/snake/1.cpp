// El classico binary search soln for Snake, in O(NlogN)
#include <cstdio>

const char *snake = "SNAKE";

char dna[100005];
int n;

// Given an integer x, determine if there
// is a snake of level x, by greedily taking
// characters
bool can(int x) {
    int j = 0, rem = x;
    for (int i = 0; i < n; i++) {
        if (dna[i] == snake[j]) {
            rem--;
            if (rem == 0) {
                if (j == 4) {
                    // Found all characters. We're done!
                    return true;
                }
                // Found x copies of the current character, so
                // switch to finding the next character.
                j++;
                rem = x;
            }
        }
    }
    // Did not finish finding characters :(
    return false;
}

int main() {
    scanf("%d%s", &n, dna);
    // Classic: binary search the answer.
    int lo = 1, hi = n;
    while (lo+1 < hi) {
        int mid = (lo+hi) / 2;
        if (can(mid)) {
            lo = mid;
        } else {
            hi = mid;
        }
    }
    printf("%d\n", lo);
    return 0;
}
