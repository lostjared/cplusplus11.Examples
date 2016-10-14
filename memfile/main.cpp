#include"memfile.hpp"
#include<iostream>
#include"memfile_hpp.hpp"


int main(int argc, char **argv) {
    
    
    mem::MemFile file, bfile;
    
    if(!file.open("./main.cpp")) {
        std::cerr << "Could not open file: \n";
        exit(EXIT_FAILURE);
    }
    
    while(!file.eof()) {
        char b;
        file.read(&b, 1);
        std::cout << b;
    }
    
    file.close();
    
    if(!bfile.open(memfile_hpp_bytes, memfile_hpp_length)) {
        std::cerr << "Could not open byte stream..\n";
        exit(EXIT_FAILURE);
    }
    
    while(!bfile.eof()) {
        char b;
        bfile.read(&b, 1);
        std::cout << b;
    }
    
    bfile.close();
    
    return EXIT_SUCCESS;
}
