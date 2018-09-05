#include <iostream>
#include <cmath>
#include <cstdio>
using namespace std;

const char* anss[] = {"no", "yes"};

int main() {
    int xi, yi, di, xc, yc, dc;
    cin >> xi >> yi >> di >> xc >> yc >> dc;
    double d = sqrt((xi-xc)*(xi-xc) + (yi-yc)*(yi-yc));
    cout << anss[abs(d-di) <= dc+1e-8] << endl;
}
