//? this code is perfect ??/
//? how could you possibly believe that it won't get 100 ??/

#include <bits/stdc++.h>
using namespace std;

const int UNDEFINED = -420;

void mistake()
{
	printf("MISTAKE\n");
	exit(0);
}

vector<pair<int, int> > edges[100005];
int colour[100005];
int leader[100005];

set<int> group_claims[100005][2];
vector<int> belong[100005];
int type[100005];

vector<int> claims[100005];
bool possible[100005];
int n, m;

int occurrences[100005];

void dfs(int at, int my_colour, int my_leader)
{
	if (colour[at] == UNDEFINED)
		colour[at] = my_colour;
	else if (colour[at] == my_colour)
		return;
	else
		mistake();

	leader[at] = my_leader;
	for (pair<int, int> other: edges[at])
	{
		if (other.second == 1)
			dfs(other.first, my_colour, my_leader);
		else
			dfs(other.first, 1-my_colour, my_leader);
	}
}

int main()
	// Step 1. Do input
	scanf("%d%d", &n, &m);
	for (int i = 0;i < m;i++)
	{
		int a, b, c; scanf("%d%d%d", &a, &b, &c);
		--a; --b;
		if (c == 3)
			claims[a].push_back(b);
		else
		{
			edges[a].push_back(make_pair(b, c));
			edges[b].push_back(make_pair(a, c));
		}
	}

	// Step 2. Run a DFS to clean up some logic, set group leaders
	for (int i = 0;i < n;i++)
		colour[i] = UNDEFINED;
	for (int i = 0;i < n;i++) if (colour[i] == UNDEFINED) 
		dfs(i, 0, i);
	for (int i = 0;i < n;i++)
		belong[leader[i]].push_back(i);

	// Step 3. Initialise stuff
	for (int i = 0;i < n;i++)
	{
		possible[i] = true; // this person is a possible culprit
		type[i] = UNDEFINED; // this group type is unknown
	}

	// Step 4. Figure out what each group is claiming
	for (int i = 0;i < n;i++) for (int u: claims[i])
		if (colour[i] == colour[leader[i]])
			group_claims[leader[i]][1].insert(u);
		else
			group_claims[leader[i]][0].insert(u);
	for (int i = 0;i < n;i++)
	{
		if (group_claims[i][0].size() > 1 && group_claims[i][1].size() > 1)
			mistake();
		if (group_claims[i][0].size() > 1)
		{
			type[i] = 1;
			for (int u: group_claims[i][0])
				possible[u] = false;
		}
		if (group_claims[i][1].size() > 1)
		{
			type[i] = 0;
			for (int u: group_claims[i][1])
				possible[u] = false;
		}
	}

	// Step 5. Check out our force-moves
	int forced = UNDEFINED;
	for (int i = 0;i < n;i++) if (type[i] != UNDEFINED)
	{
		for (int accusor: belong[i])
		{
			bool i_am_forced = false;
			if (type[i] == 1 && colour[accusor] == colour[i])
				i_am_forced = true;
			if (type[i] == 0 && colour[accusor] != colour[i])
				i_am_forced = true;
			if (i_am_forced)
			{
				for (int victim: claims[accusor]) if (possible[victim])
				{
					if (forced != UNDEFINED && forced != victim)
						mistake();
					forced = victim;
				}
			}
		}
	}
	if (forced != UNDEFINED)
	{
		printf("%d\n", forced+1);
		return 0;
	}

	// Step 6. Check out the if-else branch groups that say, either take this or take that
	// Any correct answer must be presented as an option in all of these if-else branches
	int tot_occ = 0;
	for (int i = 0;i < n;i++) if (group_claims[i][0].size() && group_claims[i][1].size())
	{
		for (int u: group_claims[i][0])
			occurrences[u]++;
		for (int u: group_claims[i][1])
			occurrences[u]++;
		tot_occ++;
	}
	set<int> options;
	for (int i = 0;i < n;i++) if (occurrences[i] == tot_occ && possible[i])
		options.insert(i);

	// Step 7. Output
	for (int i: options)
		printf("%d\n", i+1);
	if (options.empty())
		mistake();
	return 0;
}
