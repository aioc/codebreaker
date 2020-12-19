#include <bits/stdc++.h>
using namespace std;
#define MAXN 100010
int b, n;
int a[MAXN], removed[MAXN];
priority_queue<pair<int, int> , vector<pair<int, int> >, greater<pair<int, int> > > pq;
int main() {
	scanf("%d%d", &b, &n);
	for (int i = 0; i < b; i++) {
		scanf("%d", &a[i]);
		pq.emplace(a[i], i);
	}
	int currHei = 0;
	while (true) {
		int h = pq.top().first, i = pq.top().second;
		int am = (h-currHei)*pq.size();
		if (am >= n) break;
		n -= am;
		currHei = h;
		removed[i] = true;
		pq.pop();
	}
	n %= pq.size();
	if (!n) n = pq.size();
	for (int i = 0; i < b; i++) {
		if (!removed[i]) {
			n--;
			if (!n) printf("%d\n", i+1);
		}
	}
}

