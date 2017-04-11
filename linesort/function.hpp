#ifndef __FUNCTION_HPP_
#define __FUNCTION_HPP_

#include<string>
#include<iostream>
#include<vector>
#include"code.hpp"

extern interp::Code code;

namespace token {
    void token_Convert(std::vector<lex::Token> &tokens);
    void token_List(std::vector<lex::Token> &tokens);
    void token_Save(std::vector<lex::Token> &tokens);
    void token_Open(std::vector<lex::Token> &tokens);
    void token_Clear(std::vector<lex::Token> &tokens);
    void token_Remove(std::vector<lex::Token> &tokens);
    void token_Display(std::vector<lex::Token> &tokens);
}


#endif
