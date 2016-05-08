#include<iostream>
#include<string>
#include<cstdlib>
#include"memory.hpp"

int main(int argc, char **argv) {
    pool::Alloc a; // scoped memory pool
    std::cout << "Allocating to Pool....\n";
    for(unsigned int i = 0; i < 100; ++i) {
        unsigned int *buffer = (unsigned int*)a.alloc(sizeof(unsigned int));
        *buffer = rand()%0xFFFFFFFF;
        std::cout << " Allocated Address: 0x" << std::hex << (unsigned long)buffer << " value = " << std::dec << *buffer << "\n";
    }
    return 0;
    
}