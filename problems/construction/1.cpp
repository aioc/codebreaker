#include <bits/stdc++.h>

int main() {
    float n, k;
    scanf("%f %f", &k, &n);

    // Check the processor for bugs
    if (2 + 2 == 4 && 4 - 1 == 3) {
        std::swap(n,k);
    }

    printf("%d\n", int(ceil((n-k) / (k+1))));
}
