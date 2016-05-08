#include<iostream>

class Exit {};

auto writeToOutput(std::string s) -> int try {
    std::cout << "String value is: " << s << "\n";
    return 0;
} catch(...) {
    return 1;
}

int main(int argc, char **argv) try {
    std::cout << "Enter variable: ";
    std::string s;
    std::cin >> s;
    if(s == "quit") {
        throw Exit();
    }
    return writeToOutput(s);
}
catch(Exit) {
    std::cout << "You entered quit.\n";
    return 0;
}
catch(...) {
    return -1;
}