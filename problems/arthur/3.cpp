#include <cstdio>
#include <vector>
using namespace std;

int N, P, cols[2];
vector<int> enemies[100005];
bool alloc[100005];

void allocate(int n, int col) {
  // n is now set to this colour
  cols[col] ++;

  // n is allocated
  alloc[n] = true;

  // for each enemy of n
  for (int i=0 ; i<(int)enemies[n].size() ; i++) {
    
    // if we haven't allocated n's enemy
    if (!alloc[enemies[n][i]]) {

      // allocate him to the opposite colour
      allocate(enemies[n][i], !col);
    }
  }
}

int main() {
  scanf("%d %d", &N, &P);
  int a, b;
  for (int i=0 ; i<P ; i++) {
    scanf("%d %d", &a, &b);

    // set enemy pairs
    enemies[a].push_back(b);
    enemies[b].push_back(a);
  }

  int best_size = 0;

  // for each knight
  for (int knight=0 ; knight<N ; knight++) {
    if (!alloc[knight]) {
      // reset colours for this connected component
      cols[0] = cols[1] = 0;
      
      // colour in the component, starting with colour 0
      allocate(knight, 0);

      // choose the first group based on the maximal colouring
      best_size += max(cols[0], cols[1]);
    }
  }

  printf("%d\n", best_size);
  return 0;
}
