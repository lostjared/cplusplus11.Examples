#include "function.hpp"

namespace token {
    void token_Clear(std::vector<lex::Token> &v) {
        if(!interp::lines.empty()) {
            interp::lines.erase(interp::lines.begin(), interp::lines.end());
        }
    }
}
