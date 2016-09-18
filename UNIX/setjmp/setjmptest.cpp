#include<iostream>
#include<setjmp.h>

jmp_buf j_val;

int testF1(int x) {
    if(x == 1) longjmp(j_val, 1); // #1 jump from here back to setjmp return value 1
    ++x;
    return x;
}

int rtVal(int val) {
    int x_val = testF1(val);
    if(x_val == 1) {
        std::cout << "Value is: 1\n";
    }
    return x_val;
}


int main(int argc, char **argv) {
    std::cout << "Pass no arguments to test longjmp pass at least 1 to complete function\nEnter test: ";
    switch(setjmp(j_val)) { // first call retuns 0 after that value passed to longjmp
        case 0: {
            std::cout << "Returned after inital call.\n";
            if(rtVal(argc) == 3) {
                std::cout << "value is 3\n";
            } else {
                std::cout << "value is not 3\n";
            }
        }
            break;
        case 1: {
            std::cout << "We jumped back from testF1.\n";
        }
            break;
    }
    
    return EXIT_SUCCESS;
}
