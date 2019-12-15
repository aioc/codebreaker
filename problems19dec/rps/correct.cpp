#include <bits/stdc++.h>
using namespace std;

int f(int &a, int &b) {
    int r = min(a, b);
    a -= r; b -= r;
    return r;
}

int main() {
    int n;          cin >> n;
    int ra, pa, sa; cin >> ra >> pa >> sa;
    int rb, pb, sb; cin >> rb >> pb >> sb;

    int ans = f(ra, pb) + f(pa, sb) + f(sa, rb);
    f(ra, rb), f(pa, pb), f(sa, sb);
    ans -= f(rb, pa) + f(pb, sa) + f(sb, ra);

    cout << ans << endl;
    return 0;
}
