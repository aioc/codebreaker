#include <bits/stdc++.h>
using namespace std;
int a, b, c;
int he[10][100000];
bool l[10][100000];
int dr[5] = {1, -1, 0, 0, 0};
int dc[5] = {0, 0, 1, -1, 0};

int m(int r, int c)
{
	for(int i=0; i<4; i++)
	{
		int nr = r+dr[i];
		int nc = c+dc[i];
		if(nr>=0 && nc>=0 && nr<a && nc<b)
		{
			if(he[nr][nc] > he[r][c])
            {
                l[r][c] = 0;
                return 0;
            }
		}
	}
	l[r][c] = -4;
	return 1;
}

int main()
{
    FILE* e = stdin;
    FILE* f = stdout;

	fscanf(e, "%d %d %d", &a, &b, &c);
	for(int f=0; f<a; f++)
	{
		for(int c=0; c<b; c++)
		{
			fscanf(e, " %d ", &he[f][c]);
		}
	}
	int s = 0;
	for(int f=0; f<a; f++)
	{
		for(int e=0; e<b; e++)
		{
			s+= m(f, e);
		}
	}
	fprintf(f, "%d\n", s);
	for(int q=0, r, d, h; q<c; q++)
	{
		fscanf(e, "%d %d %d", &r, &d, &h);
		r--;
		d--;
		he[r][d] = h;
		for(int f=0, e, c; f<5; f++)
		{
            e = r + dr[f];
            c = d + dc[f];
			if(e>=0 && c>=0 && e<=a && c<=b)
			{
				if (l[e][c]) s--;
				s+= m(e, c);
			}
		}
		fprintf(f, "%d\n", s);
	}
}
