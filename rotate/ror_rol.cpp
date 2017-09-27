#include<iostream>
#include<bitset>

template<typename T>
T ror(T x, unsigned int m)
{
    return (x >> m) | (x << sizeof(T)*8 - m);
}
template<typename T>
T rol(T x, unsigned int m) {
    return (x << m) | (x >> (sizeof(T)*8 -m));
}

int main(int argc, char **argv) {
    std::cout << "Enter 8-bit value: ";
    unsigned int v;
    std::cin >> v;
    if(v > 255) {
        std::cerr << "Should be an 8 bit value (0-255)\n";
        exit(1);
    }
    unsigned char value = static_cast<unsigned char>(v);
    std::cout << "Rotate by:";
    unsigned int r;
    std::cin >> r;
    if(r < 1 || r > 7) {
        std::cerr << "Should be 1-7\n";
        exit(1);
    }
    std::bitset<8> before(value);
    std::cout << "Before: " << v << " = " << before << "\n";
    unsigned char left, right;
    left = rol(value, r);
    right = ror(value, r);
    std::bitset<8> after_ror(right), after_rol(left);
    std::cout << "ROR: " << static_cast<unsigned int>(right) << " = " << after_ror << "\n";
    std::cout << "ROL: " <<  static_cast<unsigned int>(left) << " = " << after_rol << "\n";
    return 0;
}
