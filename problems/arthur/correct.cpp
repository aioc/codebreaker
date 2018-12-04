// jimjam
#include <cstdio>
#include <vector>

using namespace std;

int N, P;
int tot = 0;
vector<int> rival[100005];
bool check[100005];

int max(int a, int b) {
	if (a > b) return a;
	return b;
}

int c;
int f(int x, int k) {
	int o = 1;
	c += k;
	check[x] = 1;
	for (int i = 0; i < rival[x].size(); i++) {
		if (check[rival[x][i]]) continue;
		o += f(rival[x][i], (k+1)%2);
	}

	return o;
}

int main() {
	scanf("%d %d", &N, &P);
	int a, b;
	for (int i = 0; i < P; i++) {
		scanf("%d %d", &a, &b);
		rival[a].push_back(b);
		rival[b].push_back(a);
	}

	for (int i = 1; i <= N; i++) {
		if (check[i]) continue;
		c = 0;
		int size = f(i, 1);
		tot += max(c, size-c);
	}

	printf("%d\n", tot);
}

