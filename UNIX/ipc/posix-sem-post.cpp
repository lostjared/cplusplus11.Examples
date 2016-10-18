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
        std::cerr << "Requires one argument\n" << argv[0] << " semaphore\n";
        exit(EXIT_FAILURE);
    }
    s = sem_open(argv[1], 0);
    if(s == SEM_FAILED) {
        std::cerr << "Error open semaphore failed..\n" << strerror(errno) << "\n";
        exit(EXIT_FAILURE);
    }
    if(sem_post(s) == -1) {
        std::cerr << "Semaphore post failed..\n" << strerror(errno) << "\n";
        exit(EXIT_FAILURE);
    }
    std::cout << "Post succeded\n";
    return EXIT_SUCCESS;
}
