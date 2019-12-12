#include <cstdio>
#include <queue>
using namespace std;

int arr[100005], n, k, sum, ans;

int main()
{
	scanf("%d%d", &n, &k);
	for (int i = 0;i < n;i++) scanf("%d", arr+i);
	ans = -1000000;
	deque<pair<int, int> > data;
	data.emplace_back(-1, 0);
	for (int i = 0;i < n;i++)
	{
		if (data.front().first < i-k) data.pop_front();
		sum += arr[i];
		ans = max(ans, sum-data.front().second);
		while (!data.empty() && sum <= data.back().second) data.pop_back();
		data.emplace_back(i, sum);
	}
	printf("%d\n", ans);
	return 0;
}
