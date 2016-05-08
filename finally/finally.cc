//  Created by Jared Bruni on 7/13/13.
// Idea from C++ Programming Language
// Create a function that is called when it leaves scope

// main function asks for a string and if it contains "test"
// if it does it does something
// otherwise it throws a exception

#include<iostream>


template<typename F>
class Final_release {
public:
    Final_release(F f) : fi(f) {}
    ~Final_release() {
        fi();
    }
protected:
    F fi;
};

template<typename F>
Final_release<F> finally(F f) {
    return Final_release<F>(f);
}


class TestException {};

int main(int argc, char **argv) {
    
    try {
        auto final_release = finally([]() {
            for(unsigned int i = 0; i < 10; ++i) {
                std::cout << "do stuff on release .." << i << "\n";
            }
        });
        
        std::cout << "Do this first..enter text: ";
        std::string s;
        std::cin >> s;
        if(s == "test") {
            auto final_release = finally([]() {
                std::cout << "exit: if(s == \"test\"\n";
                
            });
            std::cout << "in: if(s == \"test\"\n";
        } else throw TestException();
    }
    catch(std::exception &e) {
        std::cerr << e.what() << "\n";
    }
    catch(TestException &) {
        std::cout << "Exception wrong variable entered.\n";
    }
    
    
    return 0;
}