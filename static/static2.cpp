
#include"static_main.h"
#include<iostream>


// using a static member variable

class UserType {
public:
    UserType() {
        counter++;
    }
    static int counter;
};

int UserType::counter = 0;


// static main program style similar to Java

class Program {
public:
    static int main(int argc, char **argv) {
        
        for(int i = 0; i < 10; ++i) {
            UserType type;
        }
        
        std::cout << UserType::counter << " number created..\n";
        return 0;
    }
};


STATIC_MAIN(Program)