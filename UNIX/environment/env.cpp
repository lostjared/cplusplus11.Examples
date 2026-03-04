#include<iostream>
#include<cstdlib>

int main(void) {
    
    
    std::cout << "Path: " << getenv("PATH") << "\n";
    
    setenv("VALUE", "ONE VALUE", 0);
    
    std::cout << "Value: " << getenv("VALUE") << "\n";
    
    
    return EXIT_SUCCESS;
}
