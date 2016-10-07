#include<iostream>
#include<string>

const int OPTION_1 = 0x1, OPTION_2 = 0x2, OPTION_3 = 0x4, OPTION_4 = 0x8;

void printOptions(const int &i) {
    if((i & OPTION_1) != 0) {
        std::cout << "Option 1..\n";
    }
    
    if((i & OPTION_2) != 0) {
        std::cout << "Option 2..\n";
    }
    
    
    if((i & OPTION_3) != 0) {
        std::cout << "Option 3..\n";
    }
    
    if((i & OPTION_4) != 0) {
        std::cout << "Option 4..\n";
    }
}

int main(int argc, char **argv) {
    std::cout << "Mask #1: ";
    printOptions(OPTION_1 | OPTION_4);
    std::cout << "Mask #2: ";
    printOptions(OPTION_2 | OPTION_3);
    return 0;
}
