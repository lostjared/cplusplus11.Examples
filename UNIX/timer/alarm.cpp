#include<iostream>
#include<signal.h>
#include<unistd.h>
#include<sys/time.h>
#include<ctime>
#include<errno.h>
#include<cstring>

void alarmHandler(int sig) {
    std::cout << "Got alarm..\n";
    exit(EXIT_SUCCESS);
}

int main(int argc, char **argv) {
    
    struct sigaction sa;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sa.sa_handler = alarmHandler;
    
    if(sigaction(SIGALRM, &sa, NULL) == -1) {
        std::cerr << "Error on signal: " << strerror(errno) << "\n";
        exit(EXIT_FAILURE);
    }
    
    alarm(4);
    
    while(1) {
        std::cout << "waiting...\n";
    }
    
    return 0;
    
}
