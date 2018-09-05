#include <iostream>
#include <vector>

using namespace std;

#include<unistd.h>
#include<signal.h>
#include<cstdlib>
#include<iostream>
namespace lifeguard
{
    void handle_signal(int signal) {
        std::cout << "Caught signal " << signal << std::endl;
        std::cerr << "Caught signal " << signal << std::endl;
        exit(0);
    }
    void saveme() {
        struct sigaction sa;
        sa.sa_handler = &lifeguard::handle_signal;
        sa.sa_flags = SA_RESTART;
        sigfillset(&sa.sa_mask);

        int sig[] = {SIGFPE, SIGSEGV, SIGABRT, SIGPIPE, SIGABRT};
        int len = sizeof(sig)/sizeof(sig[0]);
        for(int i=0;i<len;i++) {
            if (sigaction(sig[i], &sa, NULL) == -1) {
                std::cerr << "Error: cannot handle signal " << sig[i] << std::endl;
                exit(1);
            }
        }
    }
}

int main() {
    lifeguard::saveme();
    int A, B, C, D;
    cin >> A >> B >> C >> D;
    int K = A-B;
    int X = A*A-B*B;
    int Y = C*C-D*D;
    int Z = X-Y;
    cout << Z/(2*K) << endl;
    return 0;
}
