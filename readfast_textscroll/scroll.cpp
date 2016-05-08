#include"lexer.hpp"
#include<iostream>
#include<string>
#include<fstream>
#include<thread>
#include<chrono>


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
            std::cout << token.getToken() << "\n";
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