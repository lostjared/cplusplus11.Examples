#include "function.hpp"

namespace token {
    void token_List(std::vector<lex::Token> &v) {
        for(auto i = interp::lines.begin(); i != interp::lines.end(); ++i) {
            std::cout << i->index << " " << i->text << "\n";
        }
    }

}
