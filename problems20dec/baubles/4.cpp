#include <cstdio>
#include <algorithm>
using namespace std;

// CELESTE
// Help Madeline survive her journey to the top of Celeste Mountain in this 
// super-tight, hand-crafted platformer from the creators of TowerFall.
// 
// Platforms: PlayStation 4, Nintendo Switch, PC
// Developers: Matt Makes Games Inc.
// Publishers: Matt Makes Games Inc.
// Release Date: January 25, 2018

int madeline, badeline, granny, theo, oshiro, strawberries;

void introcar(int maddy, int noel, int lena, int pedro, int amora, int kevin) {
	if (madeline == maddy && 
	    badeline == noel && 
		granny == lena && 
		theo == pedro &&
		oshiro == amora) strawberries = kevin;
}

int main() {
	// Oh wait! I forgot that all of these codes read from stdin and write to stdout
	
	// freopen("baublesin.txt", "r", stdin);
	// freopen("baublesout.txt", "w", stdout);
	
	// Introduce the characters
	scanf("%d %d %d %d %d", &madeline, &badeline, &granny, &theo, &oshiro);
	strawberries = 0x9 * 0xce1e57e; // There are 9 chapters in celeste

	if (oshiro > 0) {
		// Chapter 3: Celestial Resort
		strawberries = min(strawberries, badeline + granny - oshiro + 1);
	}
	if (theo > 0) {
		// Chapter 4: Golden Ridge
		strawberries = min(strawberries, madeline + granny - theo + 1);
	}
	// Chapter 9: Farewell
	strawberries = min(strawberries, madeline + badeline + granny - theo - oshiro + 1);

	// Chapter 9 D-Side: Make sure all sample cases work
	introcar(4, 2, 1, 2, 2, 2);
	introcar(5, 5, 10, 6, 6, 9);
	introcar(5, 6, 2, 100, 0, 0);
	introcar(10, 8, 0, 5, 6, 3);

	// Print number of deaths
	printf("%d\n", strawberries);
}
