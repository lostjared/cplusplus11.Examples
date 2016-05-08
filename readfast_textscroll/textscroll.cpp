#include<iostream>
#include<string>
#include<fstream>
#include"lexer.hpp"
#include<thread>
#include<chrono>
#include<sstream>

int main(int argc, char **argv) {
    
    if(argc == 3) {
        
        std::fstream source;
        source.open(argv[1], std::ios::in);
        
        if(!source.is_open()) {
            std::cerr << "Error could not open file: " << argv[1] << "\n";
            exit(0);
        }
        
        lex::Scanner scan(source);
        lex::Token token;
        unsigned int t_count = 0;
        unsigned int mill = atoi(argv[2]);
        
        while(scan.valid()) {
            scan >> token;
            if(token.getType() == lex::TOKEN_STRING) {
                std::istringstream stream(token.getToken());
                lex::Scanner scanner(stream);
                lex::Token token;
                while(scanner.valid()) {
                    scanner >> token;
                    std::cout << token.getToken() << "\n";
                    std::this_thread::sleep_for(std::chrono::milliseconds(mill));
                }
            } else {
                std::cout << token.getToken() << "\n";
                std::this_thread::sleep_for(std::chrono::milliseconds(mill));
            }
            ++t_count;
            std::this_thread::sleep_for(std::chrono::milliseconds(mill));
        }
        source.close();
        std::cout << "Printed: " << t_count << " Tokens \n";
    }
    else {
        std::cerr << "Error program requires arguments..\ntextscroll sourcefile duration\n";
    }

    return 0;
    
}