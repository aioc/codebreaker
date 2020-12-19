#include <bits/stdc++.h>
using namespace std;
int a, b, s, c, d, ans1 = 2e9, ans2 = 2e9;
int main() {
	freopen("baublesin.txt", "r", stdin);
	freopen("baublesout.txt", "w", stdout);
	scanf("%d%d%d%d%d", &a, &b, &s, &c, &d);
	if (c) ans1 = a+s-max(0, d-b)-c+1; // don't make red ones
	if (d) ans2 = b+s-max(0, c-a)-d+1; // don't make blue ones
	printf("%d\n", max(0, min(ans1, ans2)));
}
