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
        
        std::fstream out;
        out.open(argv[2], std::ios::out);
        if(!out.is_open()) {
            std::cerr << "Could not open output file: " << argv[2] << "\n";
            source.close();
            exit(0);
        }
        
        out << "<html><head><title>" << argv[1] << "</title></head><br /><body>";
        out << "<table border=\"2\"><tr><td>Index</td><td>Token</td><td>Type</td></tr>\n\n";
        
        lex::Scanner scan(source);
        lex::Token token;
        unsigned int t_count = 0;
        
        while(scan.valid()) {
            scan >> token;
            ++t_count;
            out << "<tr><td>" << t_count << "</td><td>" << token.getToken() << "</td><td>";
            out << token.getType() << "</td></tr>\n";
        }
        
        out << "</table>\n";
        out << "\n</body></html>";
        
        source.close();
        out.close();
        std::cout << "Processed: " << t_count << " Tokens \n";
    }
    else {
        std::cerr << "Error program requires arguments..\ncompress-code sourcefile outfile\n";
    }
    
    return 0;
}