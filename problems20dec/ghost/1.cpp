#include <bits/stdc++.h>
using namespace std;

long long n, k;

// s -> how many ghosts you would encounter starting at that time
map<long long, long long> counts;

int main()
{
	scanf("%lld%lld", &n, &k);

	for(long long i = 1; i < n; ++i) {
		long long x, t;
		scanf("%lld%lld", &x, &t);
		++counts[t - k * x]; // this is the required s time
	}

	// Get best time
	long long best = 0;
	for(auto& s : counts) {
		best = max(s.second, best);
	}

    printf("%lld", best);
}

