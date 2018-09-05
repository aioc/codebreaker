#include <cstdio>
#include <string>
using namespace std;

int N;
char scan[300005];
string s1, s2, target;

int len1[300005], len2[300005];

int main() {
    scanf("%d", &N);
    scanf(" %s", scan);
    s1 = string(scan);
    scanf(" %s", scan);
    s2 = string(scan);
    scanf(" %s", scan);
    target = string(scan);

    for (int i = 0; i < N; i++) if (s1[i] != target[i] && s2[i] != target[i]) {
        printf("PLAN FOILED\n");
        return 0;
    }

    for (int i = N-1; i >= 0; i--) {
        len1[i] = s1[i] == target[i] ? len1[i+1] + 1:0;
        len2[i] = s2[i] == target[i] ? len2[i+1] + 1:0;
    }

    // start with longer length? Seems Legit
    bool side = len1[0] < len2[0];
    int ans = 0;
    for (int i = 0; i < N; i++) {
        if (len1[i] < len2[i]) {
            if (!side) ans++;
            side = 1;
        } else {
            if (side) ans++;
            side = 0;
        }
    }
    printf("SUCCESS\n");
    printf("%d\n", ans);
}

