#include<iostream>
#include"databytes.hpp"

int main(int argc, char **argv) {
    
    
    unsigned int index = 0xFFFFFFFF;
    
    DataByte<unsigned int> value(index);
    
    for(unsigned int i = 0; i < value.size(); ++i) {
        std::cout << "index: " << i << " value: " << (unsigned int)value[i] << "\n";
    }
    
    
    return 0;
}