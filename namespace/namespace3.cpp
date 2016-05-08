#include<iostream>
#include<string>

namespace space1 {
    class Jared {
    public:
        void say(std::string text) {
            std::cout << "Jared: " << text << "\n";
        }
    };
}

namespace space2 {
    class Jared {
    public:
        void say(std::string text);
    };
    
    void Jared::say(std::string text) {
        std::cout << "Jared from space2: " << text << "\n";
    }
}

template<typename T>
void SayHello(T &t) {
    t.say(" Hello World");
}

int main(int argc, char **argv) {
    space1::Jared jared1;
    space2::Jared jared2;
    SayHello(jared1);
    SayHello(jared2);
    return 0;
    
}