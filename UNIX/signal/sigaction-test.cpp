#include<signal.h>
#include<unistd.h>
#include<iostream>
#include<cstring>

void output(const char *src) {
    write(1, src, strlen(src));
}

void handler(int sig) {
    output(" Caught SIGINT in Handler...\n");
}

int main() {
    struct sigaction sa;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sa.sa_handler = handler;
    
    if(sigaction(SIGINT, &sa, NULL) == -1) {
        std::cerr << "Error on sigaction: \n";
        exit(EXIT_FAILURE);
    }
    
    while(1) {
        std::cout << "Waiting for signal...\n";
        sleep(3);
    }
    
    return 0;
}
