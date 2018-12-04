#include <cstdio>

long long n, k;

int main()
{
	scanf("%lld %lld", &n, &k);

	// min possible answer: 0
	// max possible answer: 500000000

	long long lo = 0, hi = 500000000;

	// do the binary search thing
	while (lo+1 < hi)
	{
		int mid = (lo+hi) / 2;
		if (mid*(k+1) <= n)
			lo = mid;
		else
			hi = mid;
	}

	printf("%lld\n", lo);

	return 0;
}
