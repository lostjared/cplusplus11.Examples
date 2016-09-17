#include<iostream>
#include<unistd.h>
#include<fcntl.h>


int main(int argc, char **argv) {
    
    if(argc != 3) {
        std::cerr << "Error requires two arguments input output\n";
        return 0;
    }
    
    int rd_fd = open(argv[1], O_RDONLY);
    
    if(rd_fd == -1) {
        std::cerr << "Error opening input file: " << argv[1] << "\n";
        return 0;
    }
    
    int wr_fd = open(argv[2], O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
    
    if(wr_fd == -1) {
        std::cerr << "Error opening output file: " << argv[2] << "\n";
        return 0;
    }
    
    ssize_t readBytes = 0;
    char buf[1024];
    
    while((readBytes = read(rd_fd, buf, 1024)) > 0) {
        if(write(wr_fd, buf, readBytes) != readBytes) {
            std::cerr << "Error couldn't write all bytes..\n";
        }
    }
    
    close(wr_fd);
    close(rd_fd);
    
    return 0;
}
