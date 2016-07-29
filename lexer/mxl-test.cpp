#include<iostream>
#include<string>
#include<unordered_map>
#include "mxl.hpp"
#include<fstream>
#include<algorithm>

int main(int argc, char **argv) {
    
    if(argc != 2) {
        std::cerr << "Error argument required.\n";
        exit(0);
    }
    
    std::fstream file;
    file.open(argv[1], std::ios::in);
    if(!file.is_open()) {
        std::cerr << "Could not open file.\n";
        exit(0);
    }
    
    std::unordered_map<std::string, std::string> variables;
    mxl::MXLParser parser(file, variables);
    
    try {
        parser.scanSource();
        std::cout << "Scanned source found: " << parser.size() << " tokens\n";
        parser.procTokens();
        
    } catch(mxl::Parser_Error &e) {
        e.printError(std::cerr);
    } catch(lex::Scanner_EOF) {
        
    }
    parser.outputTokens(std::cout);
    file.close();
    return 0;
}
