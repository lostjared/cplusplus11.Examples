#include<iostream>
#include<string>
#include<fstream>
#include"lexer.hpp"
#include<vector>


int main(int argc, char **argv) {
    using namespace lex;
    if(argc == 2) {
        std::fstream file;
        file.open(argv[1], std::ios::in);
        if(!file.is_open()) {
            std::cerr << "Error could not open file: " << argv[1] << "\n";
            exit(0);
        }
        lex::Scanner scan(file);
        lex::Token token;
        unsigned int t_count = 0;
        int keyword_type = 0;
        int program_operators = 0;
        int program_digits = 0;
        int program_single = 0;
        int program_strings = 0;
        int program_id = 0;
        
        while(scan.valid()) {
            scan >> token;
            ++t_count;
            switch(token.getType()) {
                case TOKEN_CHAR:
                    if(token.isKeyword())
                        ++keyword_type;
                    else
                        ++program_id;
                    break;
                case TOKEN_OPERATOR:
                    ++program_operators;
                    break;
                case TOKEN_DIGIT:
                    ++program_digits;
                    break;
                case TOKEN_SINGLE:
                    ++program_single;
                    break;
                case TOKEN_STRING:
                    ++program_strings;
                default:
                    break;
            }
        }
        
        int lines = token.line;
        file.close();
        
        std::cout << lines << " Lines of code\n";
        std::cout << keyword_type << " Keywords\n";
        std::cout << program_id << " Identifiers\n";
        std::cout << program_operators << " Operators\n";
        std::cout << program_digits << " Numeric Constants\n";
        std::cout << program_single << " Character Constants\n";
        std::cout << program_strings << " String Literals\n";
        
    } else {
        std::cerr << "Error program takes one argument\n" << argv[0] << " sourcefile.cpp\n";
        exit(0);
    }
    
    return 0;
}