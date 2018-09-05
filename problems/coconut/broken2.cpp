#include<iostream>
#include<cmath>
using namespace std;
struct point{
    double x;
    double y;
};

struct arrow{
    double dx;
    double dy;

    double sqLength() {
        return dx*dx + dy*dy;
    }

    arrow scaleTo(double alpha) {
        double factor = alpha/sqrt(sqLength());
        arrow a = {dx*factor, dy*factor};
        return a;
    }
};

arrow operator*(const arrow &a, double x){
    arrow n = {a.dx*x, a.dy*x};
    return n;
}

arrow operator-(const point &a, const point &b) {
    arrow n = {a.x-b.x, a.y-b.y};
    return n;
}

point operator+(const point &a, const arrow &b){
    point n = {a.x + b.dx, a.y + b.dy};
    return n;
}

struct circle{
    point centre;
    double radius;

    bool in(point &p){
        arrow a = centre-p;
        double sql = a.sqLength();
        return a.sqLength() <= radius*radius + 1e-4;
    }

    bool on(point &p){
        arrow a = centre-p;
        double sql = a.sqLength();
        return abs(sql-radius*radius) <= 1e-4;
    }
};

bool operator==(const point &a, const point &b) {
    return a.x == b.x && a.y == b.y;
}

bool operator==(const circle &a, const circle &b) {
    return a.centre == b.centre && a.radius == b.radius;
}


int main() {
    double xi, yi, di, xc, yc, dc;
    bool intersects;
    cin >> xi >> yi >> di >> xc >> yc >> dc;

    circle i = {{xi, yi}, di}, c = {{xc, yc}, dc};
    if (i == c) {
        intersects = true;
    } else if (di == 0 && dc == 0) {
        intersects = false;
    } else if (!i.in(c.centre) and !c.in(i.centre)) {
        // Neither centre is contained in the other
        double prop = di/(di+dc);
        point inter = i.centre+(c.centre-i.centre)*prop;
        if (i.in(inter) and c.in(inter)) {
            intersects = true;
        } else {
            intersects = false;
        }
    } else {
        // Need to find a point in each circle that is not in the other
        arrow diff = c.centre-i.centre;
        point p1 = c.centre+diff.scaleTo(c.radius);
        point p2 = i.centre+diff.scaleTo(-i.radius);
        intersects = (!i.in(p1) && !c.in(p2));
    }
    cout << (intersects ? "yes" : "no") << endl;

}
