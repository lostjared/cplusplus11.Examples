#include<iostream>
#include<string>
#include<sstream>
#include"lexer.hpp"

void outputToken(std::ostream &out, const lex::Token &token) {
    if(token.getToken() == "quit") {
        out << "Quit token read from stream exiting...\n";
        exit(0);
    }
    
    if(!token.isKeyword()) {
        out << "Token: [" << token.getToken() << "] of Type: [" << token.getType() << "]\n";
    }
    else {
        out << "Token: [" << token.getToken() << "] of Type: [Keyword]\n";
    }
}
int main() {
    
    std::unordered_map<std::string, double> variables;
    std::unordered_map<std::string, lex::Func> functions;
    bool active = true;
    while(active == true) {
        try {
            std::string line;
            std::cout << "Input Text: ";
            std::getline(std::cin, line);
            std::istringstream input(line);
            lex::Parser parser(input, variables, functions);
            parser.eval();
            parser.print();
            
        }
        catch(lex::Scanner_EOF) {
            std::cerr << "Scanner End of File.\n";
            
        }
        catch(lex::Scanner_Error) {
            std::cerr << "Scanner Error..\n";
        }
    }
    return 0;
}