/* Adapted from "the Linux Programming Interface"
 Chapter 54
 */

#include<fcntl.h>
#include<sys/mman.h>
#include<unistd.h>
#include<iostream>
#include<cstring>
#include<errno.h>

int main(int argc, char **argv) {
    
    if(argc != 2) {
        std::cerr << "Requires one argument..\n" << argv[0] << " path\n";
        exit(EXIT_FAILURE);
    }
    
    if(shm_unlink(argv[1]) == -1) {
        std::cerr << "Error on shm_unlink: " << strerror(errno) << "\n";
        exit(EXIT_FAILURE);
    }
    
    return 0;
}
