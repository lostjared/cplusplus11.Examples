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
    ssize_t len;
    char *addr;
    
    if(argc != 3) {
        std::cerr << "Error requires two arguments..\n" << argv[0] << " path string\n";
        exit(EXIT_FAILURE);
    }
    
    _fd = shm_open(argv[1], O_RDWR, 0);
    if(_fd == -1)
        error("shm_open");
    
    len = strlen(argv[2]);
    if(ftruncate(_fd, len) == -1)
        error("ftruncate");
    
    std::cout << "Resized to " << len << " bytes\n";
    
    addr = (char*)mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_SHARED, _fd, 0);
    if(addr == MAP_FAILED)
        error("mmap");
    
    if(close(_fd) == -1)
        error("close");
    std::cout << "Copying " << len << " bytes.\n";
    
    memcpy(addr, argv[2], len);
    return EXIT_SUCCESS;
}

void error(const std::string &text) {
    std::cerr << "Error: " << text << "\n" << strerror(errno) << "\n";
    exit(EXIT_FAILURE);
}
