#include<iostream>
#include<string>
#include<sstream>
#include<fstream>
#include<vector>
#include"lexer.hpp"

void processTokens(std::vector<lex::Token> &t) {
    for(auto it = t.begin(), stop = t.end(); it != stop; ++it) {
        std::cout << *it << "\n";
    }
}

int main(int argc, char **argv) {
    if(argc != 2) {
        std::cerr << "Program takes one argument of source file..\n";
        return 0;
    }
    std::vector<lex::Token> tokens;
    
    try {
        std::fstream file;
        file.open(argv[1], std::ios::in);
        if(!file.is_open()) {
            std::cerr << "Error could not open file: " << argv[1] << "\n";
        }
        lex::Scanner scan(file);
        while(scan.valid()) {
            lex::Token token;
            scan >> token;
            tokens.push_back(token);
        }
        file.close();
        processTokens(tokens);
    }
    catch(lex::Scanner_EOF) {
        std::cerr << "EOF.\n\n";
    }
    catch(lex::Scanner_Error) {
        std::cerr << "Scanner Error Occured..\n";
    }
    return 0;
}