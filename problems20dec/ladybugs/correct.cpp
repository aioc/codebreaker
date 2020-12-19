#include <bits/stdc++.h>
using namespace std;
#define MAXN 100010
int n, k, q, p[MAXN], ans[MAXN];
pair<int, int> queries[MAXN];
int main() {
	scanf("%d%d%d", &n, &k, &q);
	for (int i = 0; i < n; i++) {
		scanf("%d", &p[i]);
	}
	p[n] = 1e9;
	fill_n(ans, q, 2e9);
	for (int i = 0; i < q; i++) {
		scanf("%d", &queries[i].first);
		queries[i].second = i;
		// Consider case where we just walk right
		int endPoint = distance(p, lower_bound(p, p+n, queries[i].first));
		endPoint += k-1;
		if (endPoint < n) ans[i] = min(ans[i], p[endPoint]-queries[i].first);
		// Consider case where we just walk left
		int startPoint = distance(p, upper_bound(p, p+n, queries[i].first))-1;
		startPoint -= k-1;
		if (startPoint >= 0) ans[i] = min(ans[i], queries[i].first-p[startPoint]);
	}
	sort(queries, queries+q);
	// Consider cases where we walk to the left, then to the right
	int best = 2e9;
	int j = 0;
	while (j < q && queries[j].first < p[0]) j++;
	for (int i = 0; i <= n-k; i++) {
		best = min(best, p[i+k-1]-2*p[i]);
		while (j < q && queries[j].first <= (i != n-k ? p[i+1] : 1e9)) {
			ans[queries[j].second] = min(ans[queries[j].second], best+queries[j].first);
			j++;
		}
	}
	// Consider cases where we walk to the right, then to the left
	best = 2e9;
	j = q-1;
	while (j >= 0 && queries[j].first > p[n-1]) j--;
	for (int i = n-1; i >= k-1; i--) {
		best = min(best, 2*p[i]-p[i-k+1]);
		while (j >= 0 && queries[j].first >= (i != k-1 ? p[i-1] : 0)) {
			ans[queries[j].second] = min(ans[queries[j].second], best-queries[j].first);
			j--;
		}
	}
	// Print answers
	for (int i = 0; i < q; i++) printf("%d ", ans[i]);
	printf("\n");
}
