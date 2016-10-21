/* Adapted from "the Linux Programming Interface"
 Chapter 54
 */
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/mman.h>
#include<unistd.h>
#include<cstring>
#include<errno.h>
#include<string>
#include<iostream>

void error(const std::string &text);


int main(int argc, char **argv) {
    
    int _fd;
    char *addr;
    struct stat st_buf;
    
    if(argc != 2) {
        std::cerr << "Requires one argument..\n" << argv[0] << "path \n";
        exit(EXIT_FAILURE);
    }

    _fd = shm_open(argv[1], O_RDONLY, 0);
    if(_fd == -1)
        error("shm_open");
    
    if(fstat(_fd, &st_buf) == -1)
        error("fstat");
    
    addr = (char*) mmap(NULL, st_buf.st_size, PROT_READ, MAP_SHARED, _fd, 0);
    if(addr == MAP_FAILED)
        error("mmap");
    
    if(close(_fd) == -1)
        error("close");
    
    write(STDOUT_FILENO, addr, st_buf.st_size);
    std::cout << "\n";
    
    return EXIT_SUCCESS;
}

void error(const std::string &text) {
    std::cerr << "Error: " << text << "\n" << strerror(errno) << "\n";
    exit(EXIT_FAILURE);
}
