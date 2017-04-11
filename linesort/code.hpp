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
        TextLine();
        TextLine(int index, std::string text);
        TextLine(const TextLine &t);
        bool operator<(const TextLine &t) const;
        bool operator==(const TextLine &t1) const;
        TextLine &operator=(const TextLine &t);
        
        int index;
        std::string text;
    };
    
    class Code {
    public:
        Code() {}
        void clear();
    };

    void inputText(std::vector<lex::Token> &tokens, std::string text);
    bool saveLineSource(const std::string &text);
    bool openLineSource(const std::string &text);
    void insertText(const TextLine &in);
    bool procLine(const TextLine &text, Code &code);
    
    extern std::vector<TextLine> lines;

}

#endif
