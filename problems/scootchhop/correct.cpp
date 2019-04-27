#include <bits/stdc++.h>

using namespace std;

template <typename T>
using V = vector<T>;

typedef long double ld;
typedef long long ll;

#define FO(i, N) for (int (i) = 0; (i) < (N); ++(i))
#define FOll(i, N) for (ll (i) = 0; (i) < (N); ++(i))
#define READALL(c) for (auto &e : c) { cin >> e; }
#define PRINTALL(c) for (const auto &e : c) { cout << e << " "; } cout << "\n";
#define MP(x, y) (make_pair((x), (y)))
#define MT(...) make_tuple(__VA_ARGS__)
#define ALL(x) begin(x), end(x)
#define D(x...) fprintf(stderr, x)

const int MAXN = 500, MAXQ = 1e7;
int R, C, Q;
ll DPul[MAXN+5][MAXN+5], DPbr[MAXN+5][MAXN+5], G[MAXN+5][MAXN+5], GG[MAXN+5][MAXN+5], ans[MAXQ];
tuple<int,int,int,int> Qs[MAXQ];

void fill_dp(int r, int c, int minr, int minc, int maxr, int maxc) {
	for (int i = minr-1; i <= maxr+1; ++i)
		for (int j = minc-1; j <= maxc+1; ++j)
			DPul[i][j] = DPbr[i][j] = -1e18;
	DPul[r+1][c]=0;
	for (int i = r; i >= minr; --i)
		for (int j = c; j >= minc; --j)
			DPul[i][j] = max(DPul[i+1][j],DPul[i][j+1])+G[i][j];
	DPbr[r-1][c]=0;
	for (int i = r; i <= maxr; ++i)
		for (int j = c; j <= maxc; ++j)
			DPbr[i][j] = max(DPbr[i-1][j],DPbr[i][j-1])+G[i][j];
}

void dc(int minr, int minc, int maxr, int maxc, vector<int> query_inds) {
	if (minr > maxr || minc > maxc)
		return;
	int r, c = (maxc+minc)/2;
	vector<int> query_inds_tmp;
	for (int i : query_inds) {
		int qr, qc, qrr, qcc;
		tie(qr, qc, qrr, qcc) = Qs[i];
		if (qr < minr || qc < minc || qr > maxr || qc > maxc)
			continue;
		if (qrr < minr || qcc < minc || qrr > maxr || qcc > maxc)
			continue;
		query_inds_tmp.push_back(i);
	}
	query_inds = query_inds_tmp;
	if (query_inds.size() == 0)
		return;
	for (r = minr; r <= maxr; ++r) {
		fill_dp(r, c, minr, minc, maxr, maxc);
		for (int i : query_inds) {
			int qr, qc, qrr, qcc;
			tie(qr, qc, qrr, qcc) = Qs[i];
			if (qr <= r && qrr >= r && qc <= c && qcc >= c) {
				ans[i] = max(ans[i], DPul[qr][qc]+DPbr[qrr][qcc]-G[r][c]);
			}
		}
	}
	r = (minr+maxr)/2;
	for (c = minc; c <= maxc; ++c) if (c != (maxc+minc)/2 && G[r][c] != '1') {
		fill_dp(r, c, minr, minc, maxr, maxc);
		for (int i : query_inds) {
			int qr, qc, qrr, qcc;
			tie(qr, qc, qrr, qcc) = Qs[i];
			if (qr <= r && qrr >= r && qc <= c && qcc >= c) {
				ans[i] = max(ans[i], DPul[qr][qc]+DPbr[qrr][qcc]-G[r][c]);
			}
		}
	}
	dc(minr, minc, (maxr+minr)/2-1, (maxc+minc)/2-1, query_inds);
	dc(minr, (maxc+minc)/2+1, (maxr+minr)/2-1, maxc, query_inds);
	dc((maxr+minr)/2+1, minc, maxr, (maxc+minc)/2-1, query_inds);
	dc((maxr+minr)/2+1, (maxc+minc)/2+1, maxr, maxc, query_inds);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> R >> C;
	FO(i,R) FO(j,C) {
		cin >> GG[i+1][j+1];
		G[i+1][j+1] = max(GG[i+1][j+1],0ll);
	}

	cin >> Q;
	V<int> all_inds;
	FO(i,Q) {
		int x,y,xx,yy;
		cin>>x>>y>>xx>>yy;
		Qs[i] = make_tuple(x,y,xx,yy);
		all_inds.push_back(i);
	}
    if(Q == 0) {
        Q++;
        Qs[0] = make_tuple(1, 1, R, C);
        all_inds.push_back(0);
    }

	fill(ans,ans+Q,-1e18);
	dc(1,1,R,C,all_inds);
    for(int i = 0; i < Q; i++) {
		int x,y,xx,yy;
        tie(x, y, xx, yy) = Qs[i];
        if (GG[x][y] < 0) {
          ans[i] += GG[x][y];
        }
        if (GG[xx][yy] < 0) {
          ans[i] += GG[xx][yy];
        }
    }

	FO(i,Q) cout << ans[i] << "\n";

}
