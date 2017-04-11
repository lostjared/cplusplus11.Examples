#include "lexer.hpp"

namespace lex {
    
    const char *keywords[] = {"alignof", "and", "and_eq", "asm", "auto", "bitand", "bitor", "bool", "break", "case", "catch", "char", "char16_t", "char32_t", "class", "compl", "const", "constexpr", "const_cast", "continue", "decltype", "default", "delete", "do", "double", "dynamic_cast", "else", "enum", "explicit", "export", "extern", "false", "float", "for", "friend", "goto", "if", "inline", "int", "long", "mutable", "namespace", "new", "noexcept", "not", "not_eq", "nullptr", "operator", "or", "or_eq", "private", "protected", "public", "register", "reinterpret_cast", "return", "short", "signed", "sizeof", "static", "static_assert", "static_cast", "struct", "switch", "template", "this", "thread_local", "throw", "true", "try", "typedef", "typeid", "typename", "union", "unsigned", "using", "virtual", "void", "volatile", "wchar_t", "while", "xor", "xor_eq", 0 };
    
    const char *operators[] = {"==", "!=", "<<", ">>", "+=", "-=", "*=", "/=", "&=", "|=", "^=", ";", ":", ".", "-", "(", ")", "[", "]", "{", "}", "!", "@", "#", "$", "%", "^", "&", "*", "=", "+", "~", "\"", "`", ",",  "/", ",", ">", "->", 0 };
    
	Token_map LexInput::token_map;
    
    std::ostream &operator<<(std::ostream &out, const Token_type &t) {
        static const char *strz[] = {"Nothing","Id Token","Whitespace","String","Character", "Digit","Symbol","Identifier", "\\"};
        signed int num = static_cast<signed int>(t);
        if(num >= 0 && num <= TOKEN_IDENTIFIER)
            out << strz[num];
        return out;
    }
    
    std::ostream &operator<<(std::ostream &out, const Token &t) {
        if(t.getSymbolType() != -1) {
            out << "[" << t.getToken() << "] of type: [" << t.getType() << " #: " << t.getSymbolType() << " ] Line:" << t.line <<":" << t.offset;
        }
        else
            if(t.getKeywordType() == -1)
                out << "[" << t.getToken() << "] of type: [" << t.getType() << "] Line:" << t.line <<":" << t.offset;
            else
                out << "[" << t.getToken() << "] of type: [ keyword #: " << t.getKeywordType() << "] Line: " << t.line << ":" << t.offset;;
        return out;
    }
}
