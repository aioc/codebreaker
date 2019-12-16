#include <cstdio>
#include <algorithm>

using namespace std;

int ans = 0;
// & means "reference", so any changes to
// the variables passed in as x and y will
// persist outside the function.
void drop(int& x, int &y, int d) {
    while(x && y) {
        x--;
        y--;
        ans += d;
    }
}


int i_do_not_need_this_so_im_going_to_read_it_into_an_unused_variable;

int main() {
    int Ae, Be, Ce, Am, Bm, Cm;
    scanf(" %d ", &i_do_not_need_this_so_im_going_to_read_it_into_an_unused_variable);
    scanf("%d %d %d %d %d %d", &Ae, &Be, &Cm, &Am, &Bm, &Ce);

    // Win as many as you can
    drop(Ae, Bm, 1);
    drop(Be, Cm, 1);
    drop(Ce, Am, 1);

    // Draw as many as you can
    drop(Ae, Am, 0);
    drop(Be, Bm, 0);
    drop(Ce, Cm, 0);

    // Lose the rest rip
    drop(Am, Be, -1);
    drop(Bm, Ce, -1);
    drop(Cm, Ae, -1);

    printf("%d\n", ans);
}
