#include "function.hpp"

interp::Code code;

namespace token {
    
    void token_Convert(std::vector<lex::Token> &v) {
        code.clear();
        for(unsigned int i = 0; i < interp::lines.size(); ++i) {
            if(procLine(interp::lines[i], code) == false)
                std::cerr << "Line: " << interp::lines[i].index << " contains errors.\n";
        }
    }
    
    void token_List(std::vector<lex::Token> &v) {
        for(auto i = interp::lines.begin(); i != interp::lines.end(); ++i) {
            std::cout << i->index << " " << i->text << "\n";
        }
    }
    void token_Save(std::vector<lex::Token> &v) {
        if(v[1].getTokenType() != lex::TOKEN_STRING) {
            std::cerr << "Save requires string operand in quotes.\n";
            return;
        }
        std::string filename;
        filename = v[1].getToken();
        if(interp::saveLineSource(filename)) {
            std::cout << "Saved: " << filename << "\n";
        }
    }
    void token_Open(std::vector<lex::Token> &v) {
        if(v[1].getTokenType() != lex::TOKEN_STRING) {
            std::cerr << "open requires string operand in quotes.\n";
            return;
        }
        std::string filename;
        filename = v[1].getToken();
        if(interp::openLineSource(filename)) {
            std::cout << "Loaded: " << filename << "\n";
        }
    }
    
    void token_Clear(std::vector<lex::Token> &v) {
        if(!interp::lines.empty()) {
            interp::lines.erase(interp::lines.begin(), interp::lines.end());
        }
    }
    
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
