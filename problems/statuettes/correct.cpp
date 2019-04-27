#include <cstdio>

int N;
long long p[100005], s[100005];

bool test(long long k) {
	long long x = 0;
	for (int i = 0; i < N; i++) {
		if (i) {
			if (x >= 0 && p[i]-p[i-1] > x) x = 0;
			else x -= p[i]-p[i-1];
		}
		x += s[i] - k;
	}
	return x >= 0;
}

int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++) scanf("%lld %lld", p + i, s + i);

	long long bot = 1, top = 1000000000;
	while (top != bot) {
		long long k = (bot+top)/2;
		if (test(k)) bot = k+1;
		else top = k;
	}
	printf("%lld\n", bot-1);
}

