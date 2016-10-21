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
    
    
    
    return 0;
}

void error(const std::string &text) {
    std::cerr << "Error: " << text << "\n" << strerror(errno) << "\n";
    exit(EXIT_FAILURE);
}
