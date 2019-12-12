#include <bits/stdc++.h>
#include <tr1/unordered_set>
using namespace std;

// why does my code keep on crashing in random places
// it's not functional at all
// maybe it's because I forgot to #include <functional>
#include <complex>
// guess i have to add some debug stuff now

#ifdef DEBUG
  #define D(x...) fprintf(stderr, x);
#else
  #define D(x...)
#endif

typedef long long ll;

const ll mod = 1000000007;

int main()
{
	int n, c;
	cin >> n >> c;
	vector<int> colours(n);
	for (int i = 0; i < n; i++)
	{
		cin >> colours[i];
		colours[i]--;
	}
	D("got here 1\n") // no semicolon
	int p;
	cin >> p;
	vector<tr1::unordered_set<int> > cpt(c);
	for (int i = 0; i < p; i++)
	{
		int a, b;
		cin >> a >> b;
		a--; b--;
		cpt[a].insert(b);
		cpt[b].insert(a);
	}
	D("got here 2\n") // no semicolon
	vector<int> len(c);
	for (int i = 0; i < c; i++)
		len[i] = cpt[i].size();
	vector<vector<int>> lc(c);
	for (int xi = 0; xi < c; xi++)
	{
		for (auto xj : cpt[xi])
		{
			if (len[xj] >= sqrt(p*3))
			{
				lc[xi].push_back(xj);
			}
		}
	}
	vector<ll> ways(n);
	vector<ll> wfa(c);
	vector<ll> pc(c);
	D("beginning main loop\n") // no semicolon
	for (int i = n-1; i >= 0; i--)
	{
		int xi = colours[i];
		if (len[xi] < sqrt(p*3))
		{
			ways[i] = 0;
			D("case 1 loop\n") // no semicolon
			for (auto xj : cpt[xi])
			{
				ways[i] += wfa[xj];
			}
			D("still alive haven't crashed yet\n") // no semicolon
			ways[i] %= mod;
		}
		D("#include <functional>\n") // no semicolon
		D("done case 1\n") // no semicolon
		D("right now i = %d and ways = %d\n", i, ways[i]) // no semicolon
		if (len[xi] > sqrt(p*3))
		{
			ways[i] = pc[xi];
		}
		D("done case 2\n") // no semicolon
		if (i == n-1)
		{
			ways[i] = 1;
		}
		D("done case 3\n") // no semicolon
		D("right now i = %d and ways = %d\n", i, ways[i]) // no semicolon
		wfa[xi] += ways[i];
		wfa[xi] %= mod;
		D("starting cleanup loop\n") // no semicolon
		for (auto xj : lc[xi])
		{
			pc[xj] += ways[i];
			pc[xj] %= mod;
		}
		D("done\n") // no semicolon
	}
	cout << ways[0] << "\n";
}
