#include<sys/mman.h>
#include<fcntl.h>
#include<unistd.h>
#include<iostream>
#include<string>
#include<errno.h>
#include<cstring>


static const int MEM_SIZE = 10;

void error(const std::string &text);

int main(int argc, char **argv) {
    
    char *addr;
    int _fd;
    
    if(argc != 3) {
        std::cerr << "Error requires one argument.\n" << argv[0] << " file string\n";
        exit(EXIT_FAILURE);
    }
    
    _fd = open(argv[1], O_RDWR);
    if(_fd == -1)
        error("open");
    
    addr = (char*)mmap(NULL, 10, PROT_READ | PROT_WRITE, MAP_SHARED, _fd, 0);
    if(addr == MAP_FAILED)
        error("mmap");
    
    if(close(_fd) == -1)
        error("close");
    
    std::cout  << "Current string: " << addr << "\n";
    
    if(argc > 2) {
        if(strlen(argv[2]) >= MEM_SIZE)
            error("too large of string\n");
        
        memset(addr, 0, MEM_SIZE);
        strncpy(addr, argv[2], MEM_SIZE);
        if(msync(addr, MEM_SIZE, MS_SYNC) == -1)
        	error("msync");
        std::cout << "Copied: " << argv[2] << " to shared memory\n";
        
    }
    
    return EXIT_SUCCESS;
}

void error(const std::string &text) {
    std::cerr << "Error: " << text << "\n" << strerror(errno) << "\n";
    exit(EXIT_FAILURE);
}
