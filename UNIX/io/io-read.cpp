#include<iostream>
#include<unistd.h>
#include<fcntl.h>

int main(int argc, char **argv) {
    
    if(argc != 2) {
        std::cout << "Requires one argument file to output..\n";
        return 0;
    }
    
    int fd = open(argv[1], O_RDONLY);
    
    if(fd == -1) {
        std::cerr << "Error opening file: " << argv[1] << "\n";
        return 0;
    }
    
    ssize_t bytesRead = 0;
    
    char buf [1024];
    
    while((bytesRead = read(fd, buf, 1024)) > 0) {
        if(write(STDOUT_FILENO, buf, bytesRead) != bytesRead) {
            std::cerr << "Couldn't write whole buffer..\n";
        }
    }
    close(fd);
    return 0;
}
