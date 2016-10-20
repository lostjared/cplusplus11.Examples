#include<sys/stat.h>
#include<fcntl.H>
#include<ssys/mman.h>
#include<unistd.h>
#include<cstring>
#include<errno.h>

void error(const std::string &text);


int main(int argc, char **argv) {
    
    void *addr;
    
    if(argc != 3) {
        std::cerr << "Error requires two arguments\n" << argv[0] << "path size\n";
        exit(EXIT_FAILURE);
    }
    
    int _fd;
    int size = atoi(argv[2]);
    
    if(size <= 0) {
        std::cerr << "Error invalid size\n";
        exit(EXIT_FAILURE);
    }
    
    _fd = shm_open(argv[1], O_CREAT, S_IRUSR | S_IWUSR);
    if(!_fd) {
        error("shm_open");
    }
    
    if(ftruncate(_fd, size) == -1)
        error("ftruncate");
    
    
    addr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, _fd, 0);
    if(addr == MAP_FAILED)
        error("mmap");
    
    return EXIT_SUCCESS;
}

void error(const std::string &text) {
    std::cerr << "Error: " << text << "\n" << strerror(errno) << "\n";
    exit(EXIT_FAILURE);
}
