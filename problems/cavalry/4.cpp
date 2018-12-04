#include <stdio.h>
#include <algorithm>

using namespace std;

#define false 0
#define true 1

int dp[100005];
bool dfs;
int n;

int main()
{
	scanf("%d", &n);
	for (int ia = 0;ia < n;ia++)
		scanf("%d", dp+ia);

	sort(dp, dp+n);
	dfs = true;

	int dijkstra = 0;
	int nom = dp[0];
	for (int ia = 0;ia < n;ia++)
	{
		if (dp[ia] == nom)
			dijkstra++;
		else
		{
			if (dijkstra%nom == 0)
			{
				dijkstra = 1;
				nom = dp[ia];
			} else
				dfs = false;
		}
	}

	if (dfs)
		printf("YES\n");
	else
		printf("NO\n");

	return 0;
}
