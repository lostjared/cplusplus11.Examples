/*
 Variadic template printf
 written by Jared Bruni
 http://lostsidedead.com
*/

#include<iostream>

namespace mx {
    
    void printf(const char *s) {
        if(s == nullptr) return;
        while(*s) {
            std::cout << *s++;
        }
    }
    
    template<typename T, typename... Args>
    void printf(const char *s, T value, Args... args) {
        while(s && *s) {
            if(*s == '%' && *++s!='%') {
                std::cout << value;
                return printf(++s, args...);
            }
            std::cout << *s++;
        }
        throw std::runtime_error("Extra arguments...\n");
    }
}


int main(int argc, char **argv) {
    try {
        std::string temp = "from Jared";
        mx::printf("Hello world %s %d : %d\n Test.\n",temp,640, 480);
    }
    catch(std::exception &e) {
        std::cerr << e.what() << "\n";
    }
    return 0;
}