#include<iostream>

enum class Value_type { type1, type2, type3 };

int main() {
    
    Value_type type1 = Value_type::type1;
    
    if(type1 != Value_type::type2) {
        std::cout << "Not a type 2.\n";
    }
    
    return 0;
}