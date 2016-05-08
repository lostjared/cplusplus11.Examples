/* 
   Written by Jared Bruni
   http://lostsidedead.com
   bitset ecapsulates bits
*/

#include<iostream>
#include<bitset>
#include<iomanip>

template<size_t N>
std::bitset<N> reverse_value(std::bitset<N> &value) {
    std::bitset<N> rev;
    
    for(unsigned int i = 0; i < value.size(); ++i)
        rev[(N-1)-i] = value[i];
    
    return rev;
}

int main(int argc, char **argv) {
   
    std::bitset<32> bit_value = 0x0F0F0F0F;
    std::bitset<32> rev_value;
    
    rev_value = reverse_value(bit_value);
    
    std::cout << std::setw(12) << "orig value: ";
    std::cout << std::setw(32) << bit_value << "\n";
    std::cout << std::setw(12) << "reversed: ";
    std::cout << std::setw(32) << rev_value << "\n";

    return 0;
}

