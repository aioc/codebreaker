#include <bits/stdc++.h>
using namespace std;

int arr[100005];
int n, k;

int main()
{
	scanf("%d%d", &n, &k);
	for (int i = 0;i < n;i++)
		scanf("%d", arr+i);

	int ans = *max_element(arr, arr+n);

	int lft = 0, rgt = 0, sum = 0;
	while (rgt < n) {
		sum += arr[rgt];
		rgt++;
		if (sum < 0) {
			sum = 0;
			lft = rgt;
		}
		if (rgt-lft == k+1) {
			sum -= arr[lft];
			lft++;
		}
		while (lft < rgt && arr[lft] <= 0) {
			sum -= arr[lft];
			lft++;
		}
		if (lft < rgt)
			ans = max(ans, sum);
	}

	printf("%d\n", ans);
	return 0;
}
