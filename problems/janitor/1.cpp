#include <bits/stdc++.h>
using namespace std;

// not falling for the array bounds again
// espeically the negative array index stuff
const int OFFSET = 10;

int grid[30][100020];
int R, C;

int row_updates[100020];
int col_updates[100020];
int height_updates[100020];
int Q;

int answer;

bool is_maximum(int x, int y)
{
	if (grid[OFFSET+x-1][OFFSET+y] > grid[OFFSET+x][OFFSET+y]) return false;
	if (grid[OFFSET+x+1][OFFSET+y] > grid[OFFSET+x][OFFSET+y]) return false;
	if (grid[OFFSET+x][OFFSET+y-1] > grid[OFFSET+x][OFFSET+y]) return false;
	if (grid[OFFSET+x][OFFSET+y+1] > grid[OFFSET+x][OFFSET+y]) return false;
	return true;
}

int main()
{
	scanf("%d%d%d", &R, &C, &Q);

	for (int i = 1;i <= R;i++) for (int j = 1;j <= C;j++)
		scanf("%d", &grid[OFFSET+i][OFFSET+j]);
	
	for (int i = 1;i <= Q;i++)
		scanf("%d%d%d", &row_updates[OFFSET+i], &col_updates[OFFSET+i], &height_updates[OFFSET+i]);
	
	answer = 0;
	for (int i = 1;i <= R;i++) for (int j = 1;j <= C;j++) 
		if (is_maximum(i, j))
			answer += 1;
	printf("%d\n", answer);

	for (int i = 1;i <= Q;i++)
	{
		if (is_maximum(row_updates[OFFSET+i], col_updates[OFFSET+i]))
			answer -= 1;
		if (is_maximum(row_updates[OFFSET+i]-1, col_updates[OFFSET+i]))
			answer -= 1;
		if (is_maximum(row_updates[OFFSET+i]+1, col_updates[OFFSET+i]))
			answer -= 1;
		if (is_maximum(row_updates[OFFSET+i], col_updates[OFFSET+i]-1))
			answer -= 1;
		if (is_maximum(row_updates[OFFSET+i], col_updates[OFFSET+i]+1))
			answer -= 1;

		grid[OFFSET+row_updates[OFFSET+i]][OFFSET+col_updates[OFFSET+i]] = height_updates[OFFSET+i];

		if (is_maximum(row_updates[OFFSET+i], col_updates[OFFSET+i]))
			answer += 1;
		if (is_maximum(row_updates[OFFSET+i]-1, col_updates[OFFSET+i]))
			answer += 1;
		if (is_maximum(row_updates[OFFSET+i]+1, col_updates[OFFSET+i]))
			answer += 1;
		if (is_maximum(row_updates[OFFSET+i], col_updates[OFFSET+i]-1))
			answer += 1;
		if (is_maximum(row_updates[OFFSET+i], col_updates[OFFSET+i]+1))
			answer += 1;

		printf("%d\n", answer);
	}

	return 0;
}
