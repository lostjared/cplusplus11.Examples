#include<iostream>
#include<string>


namespace space1 {
    // define in namespace
    void printString(std::string text) {
        std::cout << "Space 1: " << text << "\n";
    }
}

namespace space2 {
    // define decl only
    void printString(std::string text);
}

// implemented
void space2::printString(std::string text) {
    std::cout << "Space 2: " << text << "\n";
}

void fromHere() {
    using namespace space2;
    
    printString("Hello from here.");
}


int main(int argc, char **argv) {
    
    space1::printString("Hello World #1");
    space2::printString("Hello World #2");
    using namespace space1;
    
    printString("Hey ");
    fromHere();
    
    return 0;
}