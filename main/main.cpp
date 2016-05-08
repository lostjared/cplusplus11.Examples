#include<iostream>
#define OBJECT_MAIN(X) int main(int argc, char **argv) { return X::main(argc, argv); }

class Object {
    
    void say(std::string text) {
        std::cout << text;
    }
public:
    static int main(int argc, char **argv) {
        std::cout << "Hello world OO-style\n";
        Object o;
        o.say("Hello world from Object.\n");
        return 0;
    }
};


OBJECT_MAIN(Object);