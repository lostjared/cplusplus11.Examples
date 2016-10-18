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
    if(argc != 2) {
        std::cerr << "Requires one argument..\n" << argv[0] << " path\n";
        exit(EXIT_FAILURE);
    }
    if(sem_unlink(argv[1]) == -1) {
        std::cerr << "Error removing semaphore..\n" << strerror(errno) << "\n";
        exit(EXIT_FAILURE);
    }
    return EXIT_SUCCESS;
}
