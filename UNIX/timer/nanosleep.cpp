#include<iostream>
#include<ctime>

int main(int argc, char **argv) {
    
    if(argc != 3) {
        std::cerr << "Error arguments are:\n" << argv[0] << " seconds nanoseconds\n";
        exit(EXIT_FAILURE);
    }
    
    int seconds = atoi(argv[1]);
    long nanosec = atol(argv[2]);
    
    struct timespec s, remain;
    s.tv_sec = seconds;
    s.tv_nsec = nanosec;
    std::cout << "Sleeping for: " << seconds << " seconds and " << nanosec << " nanoseconds.\n";
    
    if(nanosleep(&s, &remain) == -1) {
        std::cout << "Sleep interupted..\n" << remain.tv_sec << " seconds and " << remain.tv_nsec << " nano seconds remaining..\n";
    } else {
        std::cout << "Slept for: " << s.tv_sec << " seconds and " << s.tv_nsec << " nanoseconds\n";
    }
    
    return EXIT_SUCCESS;
}
