#include <cstdio>

int N, M;
bool blue[100005];

int main() {
    scanf("%d %d", &N, &M);
    for (int i = 0, a, b; i < M; i++) {
        scanf("%d %d", &a, &b);
        if (a == 2 || blue[a]) {
            blue[b] = 1;
        }
    }

    int tot = 0;
    for (int i = 0; i < N; i++) if (blue[i]) tot++;

    printf("%d %d\n", M-tot+1, tot+1);
}
