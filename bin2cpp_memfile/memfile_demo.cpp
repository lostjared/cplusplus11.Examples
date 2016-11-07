#include"memfile.hpp"
#include<iostream>
#include"resource/resource.h"


int main(int argc, char **argv) {
    mem::MemFile file, bfile;
    // open from exisiting file
    if(!file.open("./memfile_demo.cpp")) {
        std::cerr << "Could not open file: \n";
        exit(EXIT_FAILURE);
    }
    // loop read each byte
    while(!file.eof()) {
        char b;
        file.read(&b, 1);
        std::cout << b;
    }
    // close file
    file.close();
    
    mem::binOutputArray("file.txt", memfile_hpp, memfile_hpp_length);
    
    // open memory
    if(!bfile.open(memfile_hpp, memfile_hpp_length)) {
        std::cerr << "Could not open byte stream..\n";
        exit(EXIT_FAILURE);
    }
    // replace first character with an @
    char c = '@';
    bfile.write(&c, 1);
    // rewind to begining
    bfile.rewind();
    // loop and read each character
    while(!bfile.eof()) {
        char b;
        bfile.read(&b, 1);
        std::cout << b;
    }
    // close memory file
    bfile.close();
    return EXIT_SUCCESS;
}
