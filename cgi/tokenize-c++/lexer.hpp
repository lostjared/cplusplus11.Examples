// Created by Jared Bruni
// http://lostsidedead.com



#ifndef lexer_lexer_h
#define lexer_lexer_h

#include<iostream>
#include<vector>
#include<cstdlib>
#include<map>

namespace lex {
    /*!
      A array of C++ keywords.
    */
    static const char *keywords[] = {"alignof", "and", "and_eq", "asm", "auto", "bitand", "bitor", "bool", "break", "case", "catch", "char", "char16_t", "char32_t", "class", "compl", "const", "constexpr", "const_cast", "continue", "decltype", "default", "delete", "do", "double", "dynamic_cast", "else", "enum", "explicit", "export", "extern", "false", "float", "for", "friend", "goto", "if", "inline", "int", "long", "mutable", "namespace", "new", "noexcept", "not", "not_eq", "nullptr", "operator", "or", "or_eq", "private", "protected", "public", "register", "reinterpret_cast", "return", "short", "signed", "sizeof", "static", "static_assert", "static_cast", "struct", "switch", "template", "this", "thread_local", "throw", "true", "try", "typedef", "typeid", "typename", "union", "unsigned", "using", "virtual", "void", "volatile", "wchar_t", "while", "xor", "xor_eq", 0 };
    
    //! An enum of C++ keywords.
    //*! Contains the keywords in same order as the keywords character array. */
    enum Keyword_type {
          KEY_ALIGNOF, KEY_AND, KEY_AND_EQ, KEY_ASM, KEY_AUTO, KEY_BITAND, KEY_BITOR, KEY_BOOL, KEY_BREAK, KEY_CASE, KEY_CATCH, KEY_CHAR, KEY_CHAR16_T, KEY_CHAR32_T, KEY_CLASS, KEY_COMPL, KEY_CONST, KEY_CONSTEXPR, KEY_CONST_CAST, KEY_CONTINUE, KEY_DECLTYPE, KEY_DEFAULT, KEY_DELETE, KEY_DO, KEY_DOUBLE, KEY_DYNAMIC_CAST, KEY_ELSE, KEY_ENUM, KEY_EXPLICIT, KEY_EXPORT, KEY_EXTERN, KEY_FALSE, KEY_FLOAT, KEY_FOR, KEY_FRIEND, KEY_GOTO, KEY_IF, KEY_INLINE, KEY_INT, KEY_LONG, KEY_MUTABLE, KEY_NAMESPACE, KEY_NEW, KEY_NOEXCEPT, KEY_NOT, KEY_NOT_EQ, KEY_NULLPTR, KEY_OPERATOR, KEY_OR, KEY_OR_EQ, KEY_PRIVATE, KEY_PROTECTED, KEY_PUBLIC, KEY_REGISTER, KEY_REINTERPRET_CAST, KEY_RETURN, KEY_SHORT, KEY_SIGNED, KEY_SIZEOF, KEY_STATIC, KEY_STATIC_ASSERT, KEY_STATIC_CAST, KEY_STRUCT, KEY_SWITCH, KEY_TEMPLATE, KEY_THIS, KEY_THREAD_LOCAL, KEY_THROW, KEY_TRUE, KEY_TRY, KEY_TYPEDEF, KEY_TYPEID, KEY_TYPENAME, KEY_UNION, KEY_UNSIGNED, KEY_USING, KEY_VIRTUAL, KEY_VOID, KEY_VOLATILE, KEY_WCHAR_T, KEY_WHILE, KEY_XOR, KEY_XOR_EQ, KEY_NULL
    };
    /*! An array of C++ symbols. */
    static const char *operators[] = {"==", "!=", "<<", ">>", "+=", "-=", "*=", "/=", "&=", "|=", "^=", ";", ":", ".", "-", "(", ")", "[", "]", "{", "}", "!", "@", "#", "$", "%", "^", "&", "*", "=", "+", "~", "\"", "`", ",",  "/", ",", ">", "->","?", 0 };
    //! Symbol type enumerated types.
    /*! All the symbols in same order as the pointer array. */
    enum Symbol_type { SYM_EEQUAL, SYM_NOTEQUAL, SYM_STREAM_LEFT, SYM_STREAM_RIGHT, SYM_PLUS_EQUAL, SYM_MINUS_EQUAL,SYM_MUL_EQUAL, SYM_DIV_EQUAL, SYM_AND_EUAL, SYM_OR_EQUAL, SYM_XOR_EQUAL,SYM_SEMICOLON, SYM_COLON, SYM_DOT, SYM_MINUS, SYM_POPEN, SYM_PCLOSE, SYM_BOPEN, SYM_BCLOSE, SYM_COPEN, SYM_CCLOSE, SYM_EXCLAMATION, SYM_AT, SYM_POUND, SYM_DOLLAR, SYM_MOD, SYM_XOR, SYM_AND, SYM_MUL, SYM_EQUAL, SYM_PLUS, SYM_TIDLE, SYM_QUOTE, SYM_ANGLE, SYM_CLASS_POINTER, SYM_QUESTION, SYM_NULL };
    
    //! Token types.
    /*! Enumerated types for the different types of tokens */
    enum Token_type { TOKEN_NOTHING=0, TOKEN_CHAR, TOKEN_WHITESPACE, TOKEN_STRING, TOKEN_SINGLE,TOKEN_DIGIT, TOKEN_OPERATOR, TOKEN_IDENTIFIER, TOKEN_PRINT, TOKEN_EOF };
    
    /*! Error types. */
    class Scanner_EOF {};
    /*! Error types. */
    class Scanner_Error {};
    /*! Error types. */
    class Exit_Exception {};

    
    /*! the Token class that encapsulates the token. */
    class Token {
    public:
        Token() {}
        //! The Token class constructor.
        /*!
        \param txt token string.
        \param t the enumerated type for representing the token.
         */
        Token(std::string txt, Token_type t) : text(txt), type(t), line(0), offset(0) {}
        //! getToken function.
        /*!
            \return Returns a string representing the token string.
         */
        std::string getToken() const { return text; }
        //! getType function.
        /*!
         \return Returns the Token_type representing the type of token string.
         */
        Token_type getType() const { return type; }
        
        //! overloaded operator = to assign token.
        /*!
         \param t the token to assign.
         \return Token returned.
         */
        Token &operator=(const Token &t) {
            setToken(t);
            return *this;
        }
        //! overloaded operator == to compare.
        /*!
            \param t Token to compare agianst.
            \return returns true if they match.
         */
        bool operator==(const Token &t) {
            if(text == t.text && type == t.type)
                return true;
            return false;
        }
        
        //! isKeyword checks if token is a keyword or not.
        /*!
            \return True if it is a keyword false if its not
         */
        bool isKeyword() {
            
            for(unsigned int i = 0; keywords[i] != 0; ++i) {
                if(keywords[i] == text) return true;
            }
            return false;
        }
        //! keywordToType converts the keyword to its Type.
        /*!
         \param text containing the text to covert 
         \return 0 or greater if true -1 if not.
         */
        int keywordToType(const std::string &text) {
            for(unsigned int i = 0; keywords[i] != 0; ++i) {
                if(text == keywords[i]) return i;
            }
            return -1;
        }
        //! symbolToType converts the string to symbol id
        /*!
         \param text contains the string to convert.
         \return 0 or greater if true -1 if false.
        */
        int symbolToType(const std::string &text) {
            for(unsigned int i = 0; operators[i] != 0; ++i) {
                if(text == operators[i]) return i;
            }
            return -1;
        }
        //! getTokenType returns the token type.
        /*!
            \return returns the token type.
         */
        Token_type getTokenType() const { return type; }
        //! Get Keyword type.
        /*!
            \return returns the keyword type.
         */
        int getKeywordType() const { return keyword_type; }
        //! Get Symbol type
        /*! \return returns the symbol type */
        int getSymbolType() const { return symbol_type; }
        
        
        //! setToken sets the token value
        /*!
         \param txt token text
         \param t  token type
         \param coffset the text location offset
         \param cline the text line location
        */
        void setToken(const std::string &txt, Token_type t, unsigned int coffset, unsigned int cline) {
            text = txt;
            keyword_type = keywordToType(text);
            symbol_type = symbolToType(text);
            type = t;
            offset = coffset;
            line = cline;
            
        }
        //! setToken set the token with another token
        /*!
            \param t the token to set
         */
        void setToken(const Token &t) {
            text = t.text;
            keyword_type = t.keyword_type;
            symbol_type = t.symbol_type;
            type = t.type;
            offset = t.offset;
            line = t.line;
        }
        
        //! overloaded operator << for Token
        friend std::ostream &operator<<(std::ostream &, const Token &);
        unsigned int line, offset;
    private:
        std::string text;
        Token_type type;
        int keyword_type;
        int symbol_type;
      
    };
    
    //! Token map for Lexical Analyzer
    class Token_map {
    public:
        unsigned char token_map[256];
        
        //! Token map constructor initalizes the object
        Token_map() {
            unsigned char i;
            
            for(i = 0; i < 0xFF; ++i) {
                token_map[i] = TOKEN_NOTHING;
            }

            for(i = 0; i < 0xFF; ++i)
                if(isOperator(i) == true)
                    token_map[i] = TOKEN_OPERATOR;
                else
                    token_map[i] = TOKEN_NOTHING;
            
            for(i = 'a'; i <= 'z'; ++i)
                token_map[i] = TOKEN_CHAR;
            for(i = 'A'; i <= 'Z'; ++i)
                token_map[i] = TOKEN_CHAR;
            
            setToken('_', TOKEN_CHAR);
            
            for(i = '0'; i <= '9'; ++i)
                token_map[i] = TOKEN_DIGIT;
            
            setToken('\'', TOKEN_SINGLE);
            setToken('"', TOKEN_STRING);
            setToken(' ', TOKEN_WHITESPACE);
            setToken('\t', TOKEN_WHITESPACE);
        }

        //! set current token type
        /*! 
         \param pos position in token map.
         \param token set token type enumerated type in token_map
        */
        void setToken(signed int pos, Token_type token) {
            token_map[pos] = token;
        }
        
        //! overloaded operator[] to access token map
        /*!
         \param pos the index in the token map.
         \return reference to that specific token.
        */
        unsigned char &operator[](char pos) {
            return token_map[static_cast<int>(pos)];
        }
        
        //! is this token a symbol?
        /*!
         
            \param c the character to check
            \return boolean value for whether or not the character is a symbol.
        */
        bool isOperator(char c) {
            static const char ch[] = ";:.-()[]{}!@#$%^&*=+~\"`,\\/<>?";
            
            for(unsigned int i = 0; ch[i] != 0; ++i)
                if(ch[i] == c)
                    return true;
            
            return false;
        }
    
    };

    class LexInput {
    private:
        bool owns;
        static Token_map token_map;
    public:
        //! Lexical Analyzer input stream constructor
        LexInput(std::istream *s) : owns(true), input(s), offset(0), line(1) {
            initMap();
        }
        //! Lexical Analyzer input stream constructor
        LexInput(std::istream &s) : owns(false), input(&s), offset(0), line(1) {
            initMap();
        }
        
        //! destructor for Lex input deletes stream if it owns it.
        ~LexInput() {
            if(owns)
                delete input;
        }
        
     
        
        void initMap() {

        }
        
        //! character to Token Type
        /*!
            \param c character to typecast
            \return return Token_type convereted from character
         */
        Token_type characterToType(const unsigned char &c) {
            return static_cast<Token_type>(token_map[c]);
        }
        
        //! getChar function to grab a character from the stream
        unsigned char getChar() {
            ++offset;
            current = input->get();
            if(current == '\n') { ++line; offset = 0; return getChar(); }
            if(*input) return current;
            return 0;
        }
        //! removeLineComment removes the single comments.
        void removeLineComment() {
            current = input->get();
            ++offset;
            if(current == '\n') { ++line; offset = 0; return; }
            while(current != '\n' && *input) {
                current = input->get();
                ++offset;
                if(!*input) break;
            }
            if(current == '\n') { ++line; offset = 0; return; }
        }
        //! remove multi line comments
        void removeMultiLineComment() {
            current = input->get();
            while(current != '*' && *input) {
                current = input->get();
                ++offset;
                if(current == '*') {
                    current = input->get();
                    ++offset;
                    if(current == '/') {
                        break;
                    }
                } else if(current == '\n') { ++line; offset = 0; }
            }
        }
        //! curChar is the current character beign scanned
        /*!
            \return returns current char
        */
        const unsigned char &curChar() const { return current; }

        
        //! putBack puts back a character into the stream.
        /*!
         
         \param c character to put back
        */
        void putBack(const unsigned char &c) {
            input->putback(c);
        }
        
        //! GetToken grabs next token from stream
        /*!
         \return returns current scanned Token 
         */
        Token GetToken() {
            Token tok;
            unsigned char c;
            if(input && input->eof()) {
              //  throw Scanner_EOF();
                tok = Token("", TOKEN_EOF);
                return tok;
            }
            c = getChar();
            if(c == 0) return Token("", TOKEN_EOF);
            Token_type type = characterToType(c);
            switch(type) {
                case TOKEN_WHITESPACE: {
                    unsigned char cc = c;
                    
                    while(cc == ' ' || cc =='\r' || cc == '\t') {
                        cc = getChar();
                    }
                    
                    putBack(cc);
                    return GetToken();
                }
                    break;
                case TOKEN_DIGIT:
                    GetDigitToken(tok);
                    break;
                case TOKEN_STRING:
                    GetStringToken(tok);
                    break;
                case TOKEN_SINGLE:
                    GetCharacterToken(tok);
                    break;
                case TOKEN_CHAR:
                    GetIdToken(tok);
                    break;
                case TOKEN_OPERATOR:
                    GetOperatorToken(tok);
                    
                    if(tok.getToken() == "//") {
                        removeLineComment();
                        return GetToken();
                    }
                    
                    if(tok.getToken() == "/*") {
                        removeMultiLineComment();
                        return GetToken();
                    }
                    
                    break;
                case TOKEN_NOTHING:
                   // std::cout << "Warning unrecognized character: " << c << "\n";
                    return GetToken();
                    break;
                default:
                    break;
            }
            ctoken = tok;
            return tok;
        }
        //! is this stream input valid? or is scanning done?
        bool valid() {
            if(input != NULL && *input)
                return true;
            return false;
        }
        //! GetCurrent token
        Token &GetCurrent() {
            return ctoken;
        }
    private:
        std::istream *input;
        unsigned int offset, line;
        unsigned char current;
        Token ctoken;
        
        void GetDigitToken(Token &token) {
            std::string tok;
            unsigned char cc = curChar();
            unsigned int sline = line, soffset = offset;
            signed int count = 0;
            bool trunc = false;
            while(((characterToType(cc) == TOKEN_DIGIT) || cc == '.') && *input) {
                if(cc == '.') ++count;
                if(count < 2)
                tok += cc;
                else { trunc = true; }
                cc = getChar();
            }
            if(characterToType(cc) !=  TOKEN_CHAR)
            putBack(cc);
            if(trunc == true) std::cout << tok << " truncated.\n";
            token.setToken(tok, TOKEN_DIGIT, soffset, sline);
        }
        
        void GetIdToken(Token &token) {
            std::string tok;
            unsigned char cc = curChar();
            unsigned int sline = line, soffset = offset;
            Token_type ccType = characterToType(cc);
            while(((ccType == TOKEN_CHAR)||(ccType == TOKEN_DIGIT))&&*input) {
                tok += cc;
                cc = getChar();
                ccType = characterToType(cc);
            }
            putBack(cc);
            token.setToken(tok, TOKEN_CHAR, soffset, sline);
         }
        
        void GetStringToken(Token &token) {
            std::string tok;
            unsigned int sline = line, soffset = offset-1;
            unsigned char prev_cc = curChar(), cc = getChar();
            Token_type ccType = characterToType(cc);
            
            while(ccType != TOKEN_STRING && *input) {
                tok += cc;
                prev_cc = cc;
                cc = getChar();
                Token_type cur_Type = characterToType(cc);
                if(prev_cc == '\\') {
                    tok += cc;
                    cc = getChar();
                    ccType = characterToType(cc);
                    continue;
                }
                ccType = characterToType(cc);
            }
            token.setToken(tok, TOKEN_STRING, soffset, sline);
        }
        
        
        void GetCharacterToken(Token &token) {
            std::string tok;
            unsigned int sline = line, soffset = offset;
            unsigned char cc = getChar();
            tok += cc;
            unsigned char cx = getChar();
            if(cc == '\\') {
                do {
                    tok += cx;
                    cx = getChar();
                } while(characterToType(cx) != TOKEN_SINGLE && *input);
            }
            token.setToken(tok, TOKEN_SINGLE, soffset, sline);
        }
        
        void GetOperatorToken(Token &token) {
            unsigned char cc = curChar();
            unsigned int sline = line, soffset = offset;
            std::string tok;
            tok += cc;
            unsigned char oc = cc;
            cc = getChar();
            if(oc == cc && (cc != '{' && cc != '[' && cc != '(' && cc != ']' && cc != ')' & cc != '}')) {
                tok += cc;
            } else if(cc == '=' || (cc == '>' && oc != '?') || cc == '*') {
                tok += cc;
            } else {
                putBack(cc);
            }
            token.setToken(tok, TOKEN_OPERATOR, soffset, sline);
        }
    };
    
    //! The Token Map
    Token_map LexInput::token_map;
    
    //! Overloaded operator << for Token Type
    std::ostream &operator<<(std::ostream &out, const Token_type &t) {
        static const char *strz[] = {"Nothing","Id Token","Whitespace","String","Character", "Digit","Symbol","Identifier", "\\"};
        signed int num = static_cast<signed int>(t);
        if(num >= 0 && num <= TOKEN_IDENTIFIER)
        out << strz[num];
     
        return out;
    }
    
    //! Overloaded operator << for the Token type
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
    
    
    //! Scanner class for interfacing the Lexical Analyzer
    class Scanner {
        
    public:
        //! Scanner constructor.
        Scanner(std::istream *str) : input(str) { }
        //! Scanner constructor.
        Scanner(std::istream &str) : input(str) { }
        
        // will throw Scanner_EOF at end of file
        //! Overloaded opreator >> for getting the next token.
        /*!
         \param token the Token to assign with value
         \return Scanner returns a reference to current object for chaining.
        */
        Scanner &operator>>(Token &token) {
            if(valid()) token = input.GetToken();
            else throw Scanner_EOF();
            return *this;
        }
        //! collect function to collect all tokens.
        void collect() {
            Token t;
            while(input.valid()) {
                t = input.GetToken();
                std::cout << t << "\n";
            }
        }
        //! Error function when a error has occoured throws Scanner_Error()
        /*!
         \param s error string.
         
        */
        void err(std::string s) {
            std::cerr << s << "\n";
            throw Scanner_Error();
        }

        //! is the input valid?
        /*!
         \return is stream valid ?
        */
        bool valid() {
            return input.valid();
        }
        
    protected:
        //! Lexical input
        LexInput input;
        //! Token current token
        Token cur_token;
    };
    
}

#endif








