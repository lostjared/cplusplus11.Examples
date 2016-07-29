#include<iostream>
#include<string>
#include<typeinfo>

class Id {
public:
    std::string first, last;
    int number;
};

class FullID : public Id {
public:
    std::string address;
    
};

int main() {
    
    Id i;
    FullID i2;
    
    std::cout << typeid(i).name() << "\n";
    std::cout << typeid(i2).name() << "\n";
    
    if(typeid(i).name()==typeid(i2).name()) {
        std::cout << "Same type\n";
    }
    else {
        std::cout << "Not the same type.\n";
    }
    
    
    return 0;
}
