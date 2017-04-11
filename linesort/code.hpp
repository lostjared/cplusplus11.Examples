#ifndef __CODE_HPP__
#define __CODE_HPP__
#include<iostream>
#include<string>
#include<cstdlib>
#include<vector>
#include<algorithm>
#include<fstream>
#include<sstream>
#include "lexer.hpp"

namespace interp {
    
    class TextLine {
    public:
        TextLine() : index(0), text("") {}
        TextLine(int index, std::string text) { this->index = index; this->text = text; }
        TextLine(const TextLine &t) {
            index = t.index;
            text = t.text;
        }
        bool operator<(const TextLine &t) const {
            return (index < t.index);
        }
        
        bool operator==(const TextLine &t1) const {
            return (index == t1.index);
        }
        TextLine &operator=(const TextLine &t) {
            index = t.index;
            text = t.text;
            return *this;
        }
        int index;
        std::string text;
    };
    
    class Code {
    public:
        
        Code() {}
        
        void clear() {
            
        }
    };

    void inputText(std::vector<lex::Token> &tokens, std::string text);
    bool saveLineSource(const std::string &text);
    bool openLineSource(const std::string &text);
    void insertText(const TextLine &in);
    bool procLine(const TextLine &text, Code &code);
    
    extern std::vector<TextLine> lines;

}

#endif
