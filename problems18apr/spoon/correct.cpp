#include <cstdio>
#include <set>
#include <cassert>
#include <deque>
#define FO(i,a,b) for (int i = (a); i < (int)b; i++)

using namespace std;

struct S {
  int t;
  bool ic;
};

bool match(char a, char b) {
  return (a == '(' && b == ')') || (a == '[' && b == ']');
}

set<int> char_pos;
int offset;

int gl() {
  return *char_pos.rbegin();
}

int gf() {
  return *char_pos.begin();
}

void el() {
  char_pos.erase(gl());
}

void ef() {
  char_pos.erase(gf());
}

void push_back(deque<S> &d, char c) {
  S ns;
  ns.t = c;
  ns.ic = true;

  //printf("push %c\n", c);
  //if (!d.empty()) printf("match? %c\n", d[offset+gl()].t);

  if (d.empty() || char_pos.empty()) {
    d.push_back(ns);
    char_pos.insert((int)d.size()-1-offset);
  } else if (match(d[offset+gl()].t, c)) {
    ns.t = 2;
    ns.ic = 0;
    while (!d.back().ic) {
      ns.t += d.back().t;
      d.pop_back();
    }
    d.pop_back();
    el();
    d.push_back(ns);
  } else {
    d.push_back(ns);
    char_pos.insert((int)d.size()-1-offset);
  }
}

void push_front(deque<S> &d, char c) {
  S ns;
  ns.t = c;
  ns.ic = true;

  //printf("push %c\n", c);
  //if (!d.empty()) printf("match? %c\n", d[offset+gl()].t);

  if (d.empty() || char_pos.empty()) {
    d.push_front(ns);
    offset++;
    char_pos.insert(0-offset);
  } else if (match(c, d[offset+gf()].t)) {
    ns.t = 2;
    ns.ic = 0;
    while (!d.front().ic) {
      ns.t += d.front().t;
      d.pop_front();
      offset--;
    }
    d.pop_front();
    offset--;
    ef();
    d.push_front(ns);
    offset++;
  } else {
    d.push_front(ns);
    offset++;
    char_pos.insert(0-offset);
  }
}

void debug(deque<S> &d) {
  printf("d:");
  FO(i,0,d.size()) {
    if (d[i].ic) printf(" %c", d[i].t);
    else printf(" %d", d[i].t);
  }
  printf("\n");
}

int main() {
  deque<S> d;
  int l;
  scanf("%d", &l);
  FO(i,0,l) {
    char c;
    scanf(" %c ", &c);
    push_back(d, c);
  }

  //debug(d);

  int n;
  scanf("%d", &n);
  FO(i,0,n) {
    int sd;
    char c;
    scanf("%d %c ", &sd, &c);
    if (sd == 1) {
      push_back(d, c);
      //debug(d);
      if (d.back().ic) printf("0\n");
      else printf("%d\n", d.back().t);
    } else {
      push_front(d, c);
      //debug(d);
      if (d.front().ic) printf("0\n");
      else printf("%d\n", d.front().t);
    }
  }

  return 0;
}
