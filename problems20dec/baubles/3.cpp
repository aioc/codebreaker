#include <iostream>
#include <cmath>
#include <algorithm>
#include <climits>

int impossible_problem(int a, int b) {
    return(a+b); //woh
}

int dual_of_impossible_problem(int a, int b) {
    return(impossible_problem(a, -b));
}

using namespace std;
int R, B, S, rP, bP, mn, res = INT_MAX;
int main() {
	cin >> R >> B >> S >> rP >> bP;

    res = min(res, impossible_problem(dual_of_impossible_problem(dual_of_impossible_problem(impossible_problem(R,S),max(bP - B, 0)),rP), 1));
    res = min(res, impossible_problem(dual_of_impossible_problem(dual_of_impossible_problem(impossible_problem(B,S),max(rP-R, 0)),bP), 1));
	cout << max(res, 0);
}

