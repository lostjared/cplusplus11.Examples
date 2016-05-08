/*
 
 written by Jared Bruni
 auto example
 
*/

#include<iostream>
#include<vector>
#include<string>
#include<sstream>

namespace driver {
    void main();
    // you can use auto for return type of a function
    
    auto temp_function(std::string s) -> decltype(s) {
        return s+"add some stuff";
    }
}


int main(int argc, char **argv) {
    driver::main();
    return 0;
}

void driver::main() {
    std::vector<std::string> ar = { "hello", "world", "this is a string" };
    auto len = ar.size();
    std::cout << "Size: " << len << "\n";
    auto loop_func = [&](std::string data) -> std::string {
        // or auto for a lambda expression
        
        std::ostringstream stream;
        // auto here insted of full def.
        
        for(auto i = ar.begin(); i != ar.end(); ++i) {
            stream << data << " " << *i << " ";
        }
        return stream.str();
    };
    std::string value;
    value = temp_function(loop_func("data := "));
    std::cout << value << "\n";
}

