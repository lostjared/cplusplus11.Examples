/* Adapted from "the Linux Programming Interface"
 Chapter 53
 */

#include<iostream>
#include<unistd.h>
#include<semaphore.h>
#include<cstring>
#include<errno.h>
#include<fcntl.h>

int main(int argc, char **argv) {

    if(argc != 3) {
        std::cerr << "Error requires two arguments..\n" << argv[0] << " path value\n";
        exit(EXIT_FAILURE);
    }
    
    sem_t *s;
    int value = atoi(argv[2]);
    
    s = sem_open(argv[1], O_CREAT, S_IRUSR | S_IWUSR, value);
    
    if(s == SEM_FAILED) {
        std::cerr << "Error initializing semaphore..\n" << strerror(errno) << "\n";
        exit(EXIT_FAILURE);
    }
    
    return 0;
}
