#include "static_main.h"

#include<iostream>


class TestProgram {
    
public:
    static int main(int argc, char **argv) {
        TestProgram program;
        program.print("Hello World\n");
        return 0;
    }
private:
    void print(std::string s) {
        std::cout << s;
    }
};

STATIC_MAIN(TestProgram)
