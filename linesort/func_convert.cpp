#include "function.hpp"

namespace token {
    void token_Convert(std::vector<lex::Token> &v) {
        code.clear();
        for(unsigned int i = 0; i < interp::lines.size(); ++i) {
            if(procLine(interp::lines[i], code) == false)
                std::cerr << "Line: " << interp::lines[i].index << " contains errors.\n";
        }
    }
}
