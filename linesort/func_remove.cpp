#include "function.hpp"

namespace token {
    void token_Remove(std::vector<lex::Token> &v) {
        if(v[1].getTokenType() != lex::TOKEN_DIGIT) {
            std::cerr << "remove requires line number.\n";
            return;
        }
        std::string index;
        index = v[1].getToken();
        int in = atoi(index.c_str());
        bool found = false;
        for(unsigned int i = 0; i < interp::lines.size(); ++i) {
            if(interp::lines[i].index == in) {
                interp::lines.erase(interp::lines.begin()+i);
                found = true;
                break;
            }
        }
        if(found == true)
            std::cout << "Line: " << in << " removed..\n";
        else
            std::cerr << "Line: " << in << " not found..\n";
        
    }
}
