/*
 Adapted from "the Linux Programming Interface"
 Chapter 53
*/


#include<iostream>
#include<unistd.h>
#include<semaphore.h>
#include<cstring>
#include<errno.h>
#include<fcntl.h>

int main(int argc, char **argv) {
    sem_t *s;
    if(argc != 2) {
        std::cerr << "Error required arguments..\n" << argv[0] << " semaphore\n";
        exit(EXIT_FAILURE);
    }
    s = sem_open(argv[1], 0);
    if(s == SEM_FAILED) {
        std::cerr << "Error opening semaphore..\n" << strerror(errno) << "\n";
        exit(EXIT_FAILURE);
    }
    if(sem_wait(s) == -1) {
        std::cerr << "Error waiting..\n";
        exit(EXIT_FAILURE);
    }
    std::cout << "wait successful\n";
    return EXIT_SUCCESS;
}
