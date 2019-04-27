#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<stack>
#include<map>
#include<fstream>

using namespace std;

bool matches(char a, char b) {
    return (a == '[' && b == ']') || (a == '(' && b == ')');
}

map<int, int> pairing;
void bracket_match(string S) {
    stack<char> s;
    stack<int> pos;
    for(int i = 0; i < S.size(); i++) {
        char cur = S[i];
        if(cur == '[' || cur == '(') {
            s.push(cur);
            pos.push(i);
        } else {
            if(s.size()) {
                if(matches(s.top(), cur)) {
                    int j = pos.top(); pos.pop();
                    s.pop();
                    pairing[i] = j;
                    pairing[j] = i;
                } else {
                    s.push('X');
                    pos.push(-1);
                }
            }
        }
    }
}

vector<int> qs;

int main() {
    ifstream in("spoon.in");
    ofstream out("spoon.out");
    int L;
    in >> L;
    string s1, s2, s3;
    in >> s2;

    int Q;
    in >> Q;
    for(int i = 0; i < Q; i++) {
        int side;
        char x;
        in >> side >> x;
        qs.push_back(side);
        if(side) {
            s3.push_back(x);
        } else {
            s1.push_back(x);
        }
    }
    reverse(begin(s1), end(s1));
    string S = s1 + s2 + s3;
    bracket_match(S);

    int l = s1.size();
    int r = s1.size() + s2.size() - 1;
    for(int i = 0; i < Q; i++) {
        if(qs[i]) {
            r++;
            if(pairing.find(r) != pairing.end() && l <= pairing[r]) {
                out << r - pairing[r] + 1 << "\n";
            } else {
                out << "0\n";
            }
        } else {
            l--;
            if(pairing.find(l) != pairing.end() && pairing[l] <= r) {
                out << pairing[l] - l + 1 << "\n";
            } else {
                out << "0\n";
            }
        }
    }
    return 0;
}
