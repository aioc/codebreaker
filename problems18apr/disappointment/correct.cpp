#include <bits/stdc++.h>
using namespace std;

vector<int> ch[100005];
int dis[100005];
int q[100005];
int n, m;

bool can(int val)
{
	for (int i = 0;i < n;i++) dis[i] = 1000000010;
	priority_queue<pair<int, int> > pq;
	dis[0] = q[0]; pq.emplace(-dis[0], 0);
	while (!pq.empty())
	{
		auto u = pq.top(); pq.pop();
		if (u.second == n-1) return true;
		if (dis[u.second]+u.first) continue;
		for (int v: ch[u.second]) if (q[v] >= dis[u.second]-val && max(dis[u.second], q[v]) < dis[v])
		{
			dis[v] = max(dis[u.second], q[v]);
			pq.emplace(-dis[v], v);
		}
	}
	return false;
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 0;i < n;i++) scanf("%d", q+i);
	for (int i = 0;i < m;i++)
	{
		int a, b; scanf("%d%d", &a, &b);
		--a, --b;
		ch[a].push_back(b);
	}
	int lo = -1, hi = 1000000010;
	// Invariant: lo always impossible, hi always possible
	while (lo+1 < hi)
	{
		int mid = (lo+hi) / 2;
		if (can(mid)) hi = mid;
		else lo = mid;
	}
	printf("%d\n", hi);
	return 0;
}
