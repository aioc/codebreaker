#include <bits/stdc++.h>
using namespace std;
int n, k, ans;
map<int, int> m;
int main() {
	scanf("%d%d", &n, &k);
	for (int i = 0; i < n; i++) {
		int x, t;
		scanf("%d%d", &x, &t);
		m[t-x*k]++;
	}
	for (auto a : m) ans = max(ans, a.second);
	printf("%d\n", ans);
}
