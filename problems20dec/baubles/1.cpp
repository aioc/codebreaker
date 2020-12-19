#include <bits/stdc++.h>
using namespace std;
int a, b, s, c, d, ans1 = 2e9, ans2 = 2e9;
int main() {
	scanf("%d%d%d%d%d", &a, &b, &s, &c, &d);
	// Whichever colour we have fewer of, make all the spares that colour.
	if(a > b) {
		a += s;
	} else {
		b += s;
	}
	int ans = a+b-c-d + 1; // Destory all red & blue
	if(c > 0) ans = min(ans, a - c + 1); // Destroy all red
	if(d > 0) ans = min(ans, b - d + 1); // Destroy all blue
	printf("%d\n", max(0, ans)); // If ans is somehow negative, make it zero
}
