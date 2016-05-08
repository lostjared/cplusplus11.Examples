#include<iostream>
#include"arraybyte.hpp"

template<typename T>
void printOut(ArrayByte<T> &value) {
    for(unsigned int i = 0; i < value.size(); ++i) {
        std::cout << "POS: " << i << " BYTE: " << (unsigned int) value[i] << "\n";
    }
}

int main(int argc, char **argv) {
    unsigned int v = 0xFFFFFFFF;
    ArrayByte<unsigned int> value(v);
   
    printOut(value);
    
    value = 0xFF00FFFE;
    
    printOut(value);
    
    return 0;
}