#include <cstdio>
#include <algorithm>
using namespace std;

#define Nmax 123456
#define Qmax 654321
int n, k, q;

int ps[Nmax];

int answer(int x, int s, int e)
{
	int best = 2e9;
	for(int i = max(0, s); i <= e && i + k <= n; ++i) {
		int a = ps[i], b = ps[i+k-1];
		int here = min(abs(b-x), abs(x-a)) + (b-a);
		best = min(best, here);
	}
	return best;
}

int main()
{
	scanf("%d%d%d", &n, &k, &q);
	for(int i = 0; i < n; ++i) scanf("%d", ps+i);
	for(int i = 0; i < q; ++i) {
		int d;
		scanf("%d", &d);
		int s = 0;
		int e = n-1;
		while (s != e) {
			int m = (s+e)/2;
			if (ps[m] > d) e = m;
			else s = m+1;
		}
		int v1 = answer(d, s-5, e+5);
		int v2 = answer(d, e-k, s-k+5);
		int v3 = answer(d, 0, 2);
		int v4 = answer(d, n-k-1, 2);
		printf("%d ", min(min(v1, v2), min(v3, v4)));
	}
	printf("\n");
}

