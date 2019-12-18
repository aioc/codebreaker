#include <iostream>

using namespace std;

int N;
int main() {
    cin >> N;
    for(int i = 1; i <= N; i++) {
        for(int j = i+1; j <= N; j++) {
            for(int k = j+1; j <= N; j++) {
                if(i + j + k == N) {
                    cout << i << " " << j << " " << k << "\n";
                    return 0;
                }
            }
        }
    }
    cout << "-1 -1 -1\n";
    return 0;
}
