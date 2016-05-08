/* union templates */

#include<iostream>

template<typename T>
union DataArray {
    T object;
    unsigned char bytes[sizeof(T)];
};

template<typename T>
std::ostream &operator<<(std::ostream &out, const DataArray<T> &d) {
    out << d.object;
    return out;
}


int main() {
    
    DataArray<unsigned int> value;
    DataArray<unsigned int> value2;
    // manipulate bytes of the integer
    value.bytes[0] = 0xFF;
    value.bytes[1] = 0xFF;
    value.bytes[2] = 0xFF;
    value.bytes[3] = 0xFF;
    // same as
    value2.object = 0xFFFFFFFF;
    
    
    std::cout << value << "\n";
    std::cout << value2 << "\n";
    
    
    value.bytes[3] = 0;
    
    std::cout << value << "\n";
    
    value.bytes[2] = 0;
    
    std::cout << value << "\n";
    
    value.bytes[1] = 0;
    
    std::cout << value << "\n";
    
    value.bytes[0] = 0;
    
    std::cout << value << "\n";
    
    
    return 0;
}