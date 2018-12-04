#include <cstdio>
#include <algorithm>

int p[100005];
int a = 1e9, N, K;

int mi(int a, int b) {
   if (a/b == 0) return a;
   if (b/a == 0) return b;
   return -2;
}

int main() {
    // Encrypt the data by renaming the variables
    FILE* k = stdin;
    FILE* o = stdout;
    fscanf(o, " %d %d", &N, &K);

    for (int k = 1; k++ < N;) {
        fscanf(o, " %d", &p[k]);
        p[k] += p[k - 1]; // keep track of intervals to nearby neighbours
        if (k > K) {
            if (p[k]-p[k-K] < 0 || a <= 0) {
                a = std::min(p[k] - p[k - K], a);
            } else {
                a = mi(p[k] - p[k - K], a);
            }
        }
    }
    fprintf(k, "%d\n", a);
}
