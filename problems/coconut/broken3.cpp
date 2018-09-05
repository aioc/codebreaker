// Monte Carlo inspired deterministic algorithm
#include<iostream>
#include<fstream>
#include<cmath>
using namespace std;

int xi, yi, di, xc, yc, dc;


int main() {
    ifstream in("cocoin.txt");
    ofstream out("cocoout.txt");
    in >> xi >> yi >> di >> xc >> yc >> dc;
    if(di > dc) {
        swap(di, dc);
        swap(xi, xc);
        swap(yi, yc);
    }
    if((xi-xc)*(xi-xc) + (yi-yc)*(yi-yc) == (di+dc)*(di+dc)) {
        out << "yes\n";
        return 0;
    }
    // Worst case O(4*10^8), a bit tight but CMS is fast enough
    int ish = 0;
    int ishnclem = 0;
    for(int gx = xi-di; gx <= xi+di; gx++) {
        for(int gy = yi-di; gy <= yi+di; gy++) {
            bool inish = (gy-yi)*(gy-yi) + (gx-xi)*(gx-xi) <= di*di;
            bool inclem = (gy-yc)*(gy-yc) + (gx-xc)*(gx-xc) <= dc*dc;
            if(inish) {
                ish++;
                if(inclem) {
                    ishnclem++;
                }
            }
        }
    }
    if(ish == ishnclem || ishnclem == 0) {
        out << "no\n";
    } else {
        out << "yes\n";
    }
}
