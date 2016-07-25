#include<iostream>
#include<string>
#include<sstream>
#include"lexer.hpp"

void outputToken(std::ostream &out, const lex::Token &token) {
    if(token.getToken() == "quit") {
        std::cout << "Quit token read from stream exiting...\n";
        exit(0);
    }
    std::cout << "Token: [" << token.getToken() << "] of Type: [" << token.getType() << "]\n";
}

int main() {
    bool active = true;
    while(active == true) {
        std::string line;
        std::cout << "Input Text: ";
        std::getline(std::cin, line);
        std::istringstream input(line);
        lex::Scanner scan(input);
        unsigned int index = 0;
        while(scan.valid()) {
            lex::Token token;
            scan >> token;
            ++index;
            std::cout << "Token Index: #" << index << ": ";
            outputToken(std::cout, token);
        }
    }
    return 0;
}