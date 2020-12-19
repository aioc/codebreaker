#include <bits/stdc++.h>
using namespace std;

int d, c0;
int p1, c1;
int p2, c2;

// days needed to pay off a, earning b per day
int days(int a, int b)
{
	if(a < 0) return 0;
	if(b == 0) return 0;
	return (a + b - 1) / b;
}

// Buy a first, then b
int simulate(int pa, int ca, int pb, int cb)
{
	int left = d;
	int cookies = 0;

	int a_need = days(pa, c0);
	if(a_need > left) return INT_MIN; // not enough time

	left -= a_need;
	cookies += a_need * c0 - pa;

	int b_need = days(pb - cookies, c0 + ca);
	if(b_need > left) return INT_MIN; // not enough time

	left -= b_need;
	cookies += b_need * (c0 + ca) - pb;

	cookies += left * (c0 + ca + cb);

	return cookies;
}

int main()
{
	scanf("%d%d%d%d%d%d", &d, &c0, &p1, &c1, &p2, &c2);

	// printf("-/- %d\n", simulate(0, 0, 0, 0));
	// printf("1/- %d\n", simulate(p1, c1, 0, 0));
	// printf("2/- %d\n", simulate(p2, c2, 0, 0));
	// printf("1/2 %d\n", simulate(p1, c1, p2, c2));
	// printf("2/1 %d\n", simulate(p2, c2, p1, c1));

	int best = max({
		simulate(0, 0, 0, 0), // do nothing
		simulate(p1, c1, 0, 0), // buy 1 only
		simulate(p2, c2, 0, 0), // buy 2 only
		simulate(p1, c1, p2, c2), // buy 1 then 2
		simulate(p2, c2, p1, c1), // buy 2 then 1
		});

	printf("%d\n", best);
}
