#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 1e5+5;

int N, K;
int sums[MAX_N];

int main() {
	scanf("%d %d", &N, &K);

	multiset<int> vals;

	for (int i=1;i<=N;i++) {
		int x;
		scanf("%d", &x);
		sums[i] = sums[i-1] + x;
	}

	int ans = -(1e9 + 5);
	for (int i=0;i<=N;i++) {
		if (!vals.empty()) {
			ans = max(ans, sums[i] - (*vals.begin()));
		}

		if (i - K >= 0) {
			vals.erase(sums[i-K]);
		}
		vals.insert(sums[i]);
	}

	printf("%d\n", ans);
	return 0;
}
