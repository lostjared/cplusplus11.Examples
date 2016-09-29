/* 
 
 To use this example
 compile and run it with
 ./nano-test seconds nanoseconds
 try something like:
 ./nano-test 30 200
 then press Ctrl+C to see how much time is left after the signal.

 */



#include<iostream>
#include<ctime>
#include<signal.h>
#include<sys/time.h>

void recursive_sleep(int seconds, long nanoseconds, struct timespec *t, struct timespec *remain);

void handler(int sig) {
    
}

int main(int argc, char **argv) {
    if(argc != 3) {
        std::cerr << "Error arguments are:\n" << argv[0] << " seconds nanoseconds\n";
        exit(EXIT_FAILURE);
    }
    int seconds = atoi(argv[1]);
    long nanosec = atol(argv[2]);
    struct sigaction sa;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sa.sa_handler = handler;
    
    if(sigaction(SIGINT, &sa, NULL) == -1) {
        std::cerr << "Error on setting up signal handler..\n";
        exit(EXIT_FAILURE);
    }
    struct timespec s, remain;
    s.tv_sec = seconds;
    s.tv_nsec = nanosec;
    std::cout << "Sleeping for: " << seconds << " seconds and " << nanosec << " nanoseconds.\n";
    recursive_sleep(seconds, nanosec, &s, &remain);
    return EXIT_SUCCESS;
}


void recursive_sleep(int seconds, long nanoseconds, struct timespec *t, struct timespec *remain) {
    std::cout << "Going to sleep..\n";
    if(nanosleep(t, remain) == -1) {
        std::cout << " Sleep interupted..\n" << remain->tv_sec << " seconds and " << remain->tv_nsec << " nano seconds remaining..\n";
        struct timespec old;
        recursive_sleep(seconds, nanoseconds, remain, &old);
        return;
    } else {
        std::cout << "Slept for: " << seconds << " seconds and " << nanoseconds << " nanoseconds\n";
    }
}
