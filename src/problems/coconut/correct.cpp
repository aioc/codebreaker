#include <bits/stdc++.h>

int ax, ay, ad, bx, by, bd;

void ans(bool cons) {
    printf("%s\n", cons ? "yes" : "no");
}

int main() {
//    freopen("cocoin.txt", "r", stdin);
//    freopen("cocoout.txt", "w", stdout);
    scanf("%d%d%d", &ax, &ay, &ad);
    scanf("%d%d%d", &bx, &by, &bd);

    // this solution goes by the problem statement and sample data where
    // consistent means 'exactly 1 solution'

    if (ax == bx && ay == by) {
        ans(ad == bd);
    } else {
        int squaredist = (ax - bx) * (ax - bx) + (ay - by) * (ay - by);
        ans(squaredist <= (ad + bd) * (ad + bd) &&
            squaredist >= (ad - bd) * (ad - bd));
    }
}
