#include <bits/stdc++.h>
using namespace std;

int red, blue, spare, red_order, blue_order;

int main() {
	cin >> red >> blue >> spare >> red_order >> blue_order;

	// make the necessary baubles first
	int red_made = max(red_order - red, 0);
	int blue_made = max(blue_order - blue, 0);
	spare -= red_made + blue_made;

	// find how many excess baubles need to be destroyed
	int red_excess = max(red - red_order, 0);
	int blue_excess = max(blue - blue_order, 0);

	// if there are no baubles ordered of that colour, excess is set to over maximum
	// this ensures that this colour is never chosen
	if (red_order == 0) red_excess = 50000005;
	if (blue_order == 0) blue_excess = 50000005;

	int ans;

	// if the order could never be fulfilled
	if (spare < 0) {
		ans = 0;
	} else {
		ans = min(red_excess, blue_excess) + spare + 1;
	}

	cout << ans;
}
