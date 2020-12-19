#include <iostream>

using namespace std;

int P1, C1; // price cookies
int P2, C2; // pruce cookies
int DAYS, RATE;

int main() {
    cin >> DAYS >> RATE;
    cin >> P1 >> C1;
    cin >> P2 >> C2;

    if(P1 > P2) {
        swap(P1, C1);
        swap(P2, C2);
    }

    int curMoney = 0;
    int day = 0;
    // Wait till we can afford factory 1
    while(curMoney < P1) {
        curMoney += RATE;
        day++;
    }

    curMoney -= P1;
    RATE += C1;

    // Wait till we can afford factory 2
    while(curMoney < P2) {
        curMoney += RATE;
        day++;
    }

    curMoney -= P2;
    RATE += C2;

    // Wait till the end of time
    while(day < DAYS) {
        day++;
        curMoney += RATE;
    }

    cout << curMoney << "\n";
}

