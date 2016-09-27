#include<iostream>
#include<signal.h>
#include<sys/time.h>
#include<ctime>
#include<unistd.h>
#include<errno.h>
#include<cstring>


static volatile sig_atomic_t alarmSet = 0;

void timerHandler(int sig) {
    alarmSet = 1;
}

int main(int argc, char **argv) {
    
    struct itimerval time_val;
    int max_timeouts = 0;
    int timeouts = 0;
    
    struct sigaction sa;
    
    std::cout << "Program will now wait for the timer to send a signal..\n";
    
    timeouts = 0;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sa.sa_handler = timerHandler;
    if(sigaction(SIGALRM, &sa, NULL) == -1) {
        std::cerr << "Signal Error: " << strerror(errno) << "\n";
        exit(EXIT_FAILURE);
    }
    
    time_val.it_value.tv_sec = 3;
    time_val.it_value.tv_usec = 1;
    time_val.it_interval.tv_sec = 3;
    time_val.it_interval.tv_usec = 1;
    
    max_timeouts = 4;
    if(setitimer(ITIMER_REAL, &time_val, NULL) == -1) {
        std::cerr << "Set Timer Error:" << strerror(errno) << "\n";
        exit(EXIT_FAILURE);
    }
    
    timeouts = 0;
    
    while(1) {
        
        if(alarmSet == 1) {
            alarmSet = 0;
            std::cout << "Alarm went off...\n";
            timeouts++;
            if(timeouts >= max_timeouts) {
                std::cout << "Timers captured..\n";
                exit(EXIT_FAILURE);
            }
        }
        
    }
    
    return 0;
}
