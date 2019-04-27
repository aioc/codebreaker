#include <bits/stdc++.h>
using namespace std;

long long p[100002];
long long s[100002];
long long c[100002];
int n;

bool attempt(const long long each) {
	for (int i = 0;i < n;i++)
		c[i] = s[i];
	for (int i = 0;i < n-1;i++) {
		long long diff = each - c[i];
		if (diff < 0ll) {
			diff = -diff;
			if (diff > p[i+1]-p[i])
				c[i+1] = c[i+1] + (diff - (p[i+1] - p[i]));
		} else {
			c[i] += diff;
			c[i+1] -= diff;
			c[i+1] -= (p[i+1] - p[i]);
		}
	}
	return (c[n-1] >= each);
}

int main()
{
	scanf("%d", &n);
	for (int i = 0;i < n;i++)
		scanf("%lld%lld", p+i, s+i);
	if (n == 1) {
		printf("%lld\n", s[0]);
		return 0;
	}

	long long lo = 0ll, hi = 100000000000010ll;
	while (lo < hi-1ll) {
		long long mid = (lo + hi) >> 1ll;
		bool a = attempt(mid);
		bool b = attempt(mid+1ll);
		if (a == b) {
			if (a) lo = mid + 1ll;
			else   hi = mid;
		} else {
			lo = mid;
			break;
		}
	}
	printf("%lld\n", lo);
	return 0;
}
