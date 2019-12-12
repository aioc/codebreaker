#include <stdio.h>

int N;

char stuff[1000001];

int front = 200001;
int back = 200000;
int pos[1000001];
char curStr[1000001];

int addFront(char c, int p) {
    if (front > back) {
        pos[front--] = p;
        curStr[front] = c;
        return 0;
    } else {
        if ((c == '(' && curStr[front] == ')') || (c == '[' && curStr[front] == ']')) {
            return pos[front] - p + 1;
        } else {
            pos[--front] = p;
            curStr[front] = c;
            return 0;
        }
    }
}

int addBack(char c, int p) {
    if (front > back) {
        pos[back++] = p;
        curStr[back] = c;
        return 0;
    } else {
        if ((c == ')' && curStr[back] == '(') || (c == ']' && curStr[back] == '[')) {
            return p - pos[back--] + 1;
        } else {
            pos[++back] = p;
            curStr[back] = c;
            return 0;
        }
    }
}

int main () {
    scanf ("%d ", &N);
    int i;
    scanf ("%s ", &stuff[0]);
    for (i = 0; i < N; i++) {
        addBack(stuff[i], i);
    }
    int q;
    int posF = 0;
    int posB = N - 1;
    scanf ("%d ", &q);
    for (i = 0; i < q; i++) {
        int s;
        char c;
        scanf ("%d %c ", &s, &c);
        int res = 0;
        if (s) {
            res = addBack(c, ++posB);
        } else {
            res = addFront(c, --posF);
        }
        printf ("%d\n", res);
    }
    return 0;
}
