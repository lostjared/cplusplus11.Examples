#include "function.hpp"

namespace token {
    void token_Display(std::vector<lex::Token> &v) {
        if(v[1].getTokenType() != lex::TOKEN_DIGIT) {
            std::cerr << "display requires line number.\n";
            return;
        }
        std::string index;
        index = v[1].getToken();
        bool found = false;
        int in = atoi(index.c_str());
        for(unsigned int i = 0; i < interp::lines.size(); ++i) {
            if(interp::lines[i].index == in) {
                std::cout << interp::lines[i].index << " " << interp::lines[i].text << "\n";
                found = true;
                break;
            }
        }
        if(found == false) {
            std::cerr << "Index: " << in << " not found!\n";        }
        
    }  
}
