#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> pii;

const int MAX_N = 1e5+5;

int N, K;

int main() {
	scanf("%d %d", &N, &K);

	int cur = 0;
	// A deque gives O(1) push/pop from front/back,
	// which you can use to solve panorame in O(N)!
	deque<pii> deck;
	deck.emplace_back(0, 0);

	int ans = 0;
	for (int i=1;i<=N;i++) {
		int x;
		scanf("%d", &x);
		cur += x;

		ans = max(ans, cur - deck.front().second);

		if (deck.front().first == i - K) {
			deck.pop_front();
		}

		while (!deck.empty() && deck.back().second >= cur) {
			deck.pop_back();
		}
		deck.emplace_back(i, cur);
	}

	printf("%d\n", ans);
}
