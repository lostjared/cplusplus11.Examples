#include<iostream>
#include<setjmp.h>

jmp_buf j_val;

int testF1() {
    int x = 0;
    longjmp(j_val, 1); // #1 jump from here back to setjmp return value 1
    std::cin >> x;
    return x;
}

int rtVal() {
    int x_val = testF1();
    ++x_val;
    return x_val;
}


int main() {
    std::cout << "Enter test: ";
    switch(setjmp(j_val)) { // first call retuns 0 after that value passed to longjmp
        case 0: {
            std::cout << "Returned after inital call.\n";
            
            if(rtVal() == 2) {
                std::cout << "value is 2\n";
            } else {
                std::cout << "value is not 2\n";
            }
            
        }
        case 1: {
            std::cout << "We jumped back from testF1.\n";
        }
            break;
    }
    
    return EXIT_SUCCESS;
}
