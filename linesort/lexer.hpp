// Created by Jared Bruni
// http://lostsidedead.com



#ifndef lexer_lexer_h
#define lexer_lexer_h

#include<iostream>
#include<vector>
#include<cstdlib>
#include<unordered_map>

namespace lex {
    
    extern const char *keywords[];
    
    enum Keyword_type {
          KEY_ALIGNOF, KEY_AND, KEY_AND_EQ, KEY_ASM, KEY_AUTO, KEY_BITAND, KEY_BITOR, KEY_BOOL, KEY_BREAK, KEY_CASE, KEY_CATCH, KEY_CHAR, KEY_CHAR16_T, KEY_CHAR32_T, KEY_CLASS, KEY_COMPL, KEY_CONST, KEY_CONSTEXPR, KEY_CONST_CAST, KEY_CONTINUE, KEY_DECLTYPE, KEY_DEFAULT, KEY_DELETE, KEY_DO, KEY_DOUBLE, KEY_DYNAMIC_CAST, KEY_ELSE, KEY_ENUM, KEY_EXPLICIT, KEY_EXPORT, KEY_EXTERN, KEY_FALSE, KEY_FLOAT, KEY_FOR, KEY_FRIEND, KEY_GOTO, KEY_IF, KEY_INLINE, KEY_INT, KEY_LONG, KEY_MUTABLE, KEY_NAMESPACE, KEY_NEW, KEY_NOEXCEPT, KEY_NOT, KEY_NOT_EQ, KEY_NULLPTR, KEY_OPERATOR, KEY_OR, KEY_OR_EQ, KEY_PRIVATE, KEY_PROTECTED, KEY_PUBLIC, KEY_REGISTER, KEY_REINTERPRET_CAST, KEY_RETURN, KEY_SHORT, KEY_SIGNED, KEY_SIZEOF, KEY_STATIC, KEY_STATIC_ASSERT, KEY_STATIC_CAST, KEY_STRUCT, KEY_SWITCH, KEY_TEMPLATE, KEY_THIS, KEY_THREAD_LOCAL, KEY_THROW, KEY_TRUE, KEY_TRY, KEY_TYPEDEF, KEY_TYPEID, KEY_TYPENAME, KEY_UNION, KEY_UNSIGNED, KEY_USING, KEY_VIRTUAL, KEY_VOID, KEY_VOLATILE, KEY_WCHAR_T, KEY_WHILE, KEY_XOR, KEY_XOR_EQ, KEY_NULL
    };

    extern const char *operators[];
    
    enum Symbol_type { SYM_EEQUAL, SYM_NOTEQUAL, SYM_STREAM_LEFT, SYM_STREAM_RIGHT, SYM_PLUS_EQUAL, SYM_MINUS_EQUAL,SYM_MUL_EQUAL, SYM_DIV_EQUAL, SYM_AND_EUAL, SYM_OR_EQUAL, SYM_XOR_EQUAL,SYM_SEMICOLON, SYM_COLON, SYM_DOT, SYM_MINUS, SYM_POPEN, SYM_PCLOSE, SYM_BOPEN, SYM_BCLOSE, SYM_COPEN, SYM_CCLOSE, SYM_EXCLAMATION, SYM_AT, SYM_POUND, SYM_DOLLAR, SYM_MOD, SYM_XOR, SYM_AND, SYM_MUL, SYM_EQUAL, SYM_PLUS, SYM_TIDLE, SYM_QUOTE, SYM_ANGLE, SYM_CLASS_POINTER, SYM_NULL };
    
    enum Token_type { TOKEN_NOTHING=0, TOKEN_CHAR, TOKEN_WHITESPACE, TOKEN_STRING, TOKEN_SINGLE,TOKEN_DIGIT, TOKEN_OPERATOR, TOKEN_IDENTIFIER, TOKEN_PRINT, TOKEN_EOF };
    
    class Scanner_EOF {};
    class Scanner_Error {};
    class Exit_Exception {};

    class Token {
    public:
        Token() {}
        Token(std::string txt, Token_type t) : text(txt), type(t), line(0), offset(0) {}
        std::string getToken() const { return text; }
        Token_type getType() const { return type; }
        
        Token &operator=(const Token &t) {
            setToken(t);
            return *this;
        }
        
        bool operator==(const Token &t) {
            if(text == t.text && type == t.type)
                return true;
            return false;
        }
        
        bool isKeyword() {
            
            for(unsigned int i = 0; keywords[i] != 0; ++i) {
                if(keywords[i] == text) return true;
            }
            return false;
        }
        
        int keywordToType(const std::string &text) {
            for(unsigned int i = 0; keywords[i] != 0; ++i) {
                if(text == keywords[i]) return i;
            }
            return -1;
        }
        
        int symbolToType(const std::string &text) {
            for(unsigned int i = 0; operators[i] != 0; ++i) {
                if(text == operators[i]) return i;
            }
            return -1;
        }
        
        Token_type getTokenType() const { return type; }
        int getKeywordType() const { return keyword_type; }
        int getSymbolType() const { return symbol_type; }
        
        void setToken(const std::string &txt, Token_type t, unsigned int coffset, unsigned int cline) {
            text = txt;
            keyword_type = keywordToType(text);
            symbol_type = symbolToType(text);
            type = t;
            offset = coffset;
            line = cline;
            
        }
        void setToken(const Token &t) {
            text = t.text;
            keyword_type = t.keyword_type;
            symbol_type = t.symbol_type;
            type = t.type;
            offset = t.offset;
            line = t.line;
        }
        
        friend std::ostream &operator<<(std::ostream &, const Token &);
        
        unsigned int line, offset;
    private:
        std::string text;
        Token_type type;
        int keyword_type;
        int symbol_type;
      
    };
    
    class Token_map {
    public:
        unsigned char token_map[256] = { TOKEN_NOTHING };
        
        Token_map() {
            unsigned char i;
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

        void setToken(signed int pos, Token_type token) {
            token_map[pos] = token;
        }
        
        
        
        unsigned char &operator[](char pos) {
            return token_map[static_cast<int>(pos)];
        }
        
        bool isOperator(char c) {
            static const char ch[] = ";:.-()[]{}!@#$%^&*=+~\"`,\\/<>";
            
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
         LexInput(std::istream *s) : owns(true), input(s), offset(0), line(1) {
            initMap();
        }
        LexInput(std::istream &s) : owns(false), input(&s), offset(0), line(1) {
            initMap();
        }
        
        ~LexInput() {
            if(owns)
                delete input;
        }
        
     
        
        void initMap() {

        }
        
        Token_type characterToType(const unsigned char &c) {
            return static_cast<Token_type>(token_map[c]);
        }
        
        unsigned char getChar() {
            ++offset;
            current = input->get();
            if(current == '\n') { ++line; offset = 0; return getChar(); }
            if(*input) return current;
            return 0;
        }
        
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
        
        const unsigned char &curChar() const { return current; }

        void putBack(const unsigned char &c) {
            input->putback(c);
        }
        
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
                    std::cout << "Warning unrecognized character: " << c << "\n";
                    return GetToken();
                    break;
                default:
                    break;
            }
            ctoken = tok;
            return tok;
        }
        
        bool valid() {
            if(input != nullptr && *input)
                return true;
            return false;
        }
        
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
            if(oc == cc && (cc != '{' && cc != '[' && cc != '(' && cc != ']' && cc != ')' && cc != '}')) {
                tok += cc;
            } else if(cc == '=' || cc == '>' || cc == '*') {
                tok += cc;
            } else {
                putBack(cc);
            }
            token.setToken(tok, TOKEN_OPERATOR, soffset, sline);
        }
    };

    std::ostream &operator<<(std::ostream &out, const Token_type &t);
    std::ostream &operator<<(std::ostream &out, const Token &t);

    class Scanner {
        
    public:
        Scanner(std::istream *str) : input{str} { }
        Scanner(std::istream &str) : input(str) { }
        
        // will throw Scanner_EOF at end of file
        Scanner &operator>>(Token &token) {
            if(valid()) token = input.GetToken();
            else throw Scanner_EOF();
            return *this;
        }
        
        void collect() {
            Token t;
            while(input.valid()) {
                t = input.GetToken();
                std::cout << t << "\n";
            }
        }
        
        void err(std::string s) {
            std::cerr << s << "\n";
            throw Scanner_Error();
        }

    
        bool valid() {
            return input.valid();
        }
        
    protected:
        LexInput input;
        Token cur_token;
    };
      
    struct Func { //use default constuctor
        std::string name;
        double (*func)(double d);
    };
            
    class Parser : public Scanner {
    private:
        std::unordered_map<std::string, double> &vars;
        std::unordered_map<std::string, Func> &function;
    public:
        explicit Parser(std::istream *stream, std::unordered_map<std::string, double> &v, std::unordered_map<std::string, Func> &f) : Scanner{stream}, vars(v), function(f) {}
        explicit Parser(std::istream &stream, std::unordered_map<std::string, double> &v, std::unordered_map<std::string, Func> &f) : Scanner{stream}, vars{v}, function{f} {}
        bool eval() {
            try {
                while(1) {
                    Token t = input.GetToken();
                    if(t.getType() == TOKEN_EOF) {
                        return true;
                    }
            
                    std::cout << "Expression  Value: " << expr(false) << "\n";
            
                    if(input.GetCurrent().getToken() == ";")
                        continue;// eat token
                
                }
            }
            catch (Scanner_EOF) {
                std::cout << "end of evalulation.\n";
            }
            catch(Scanner_Error) {
                std::cout << " A error has occoured.\n";
            }
            return false;
        }
        
        double prim(bool get) {
            
            if(get) input.GetToken();
            switch(input.GetCurrent().getType()) {
                case TOKEN_EOF:
                    throw lex::Scanner_EOF();
                    break;
                case TOKEN_DIGIT: {
                    double v = atof(input.GetCurrent().getToken().c_str());
                    input.GetToken();
                    return v;
                }
                    break;
                case TOKEN_CHAR: {
                    std::string var_name = input.GetCurrent().getToken();
                    input.GetToken();
                    if(input.GetCurrent().getToken() == "(") {
                        if (function.find(var_name) != function.end()) {
                            double d = expr(true);
                            if(input.GetCurrent().getToken() != ")") {
                                err("missing closing ).");
                                
                            }
                            
                            input.GetToken();
                            
                            if(function[var_name].func != 0)
                            return function[var_name].func(d);
                            
                            err("Error function not found.\n");
                        } else err("Unknown function");
                    }
                    
                    double &v = vars[var_name];
                    if(input.GetCurrent().getToken() == "=")  {
                        v = expr(true);
                    } else if(input.GetCurrent().getToken() == "+=") {
                        v += expr(true);
                        
                    } else if(input.GetCurrent().getToken() == "-=") {
                        v -= expr(true);
                    } else if(input.GetCurrent().getToken() == "*=") {
                        v *= expr(true);
                    } else if(input.GetCurrent().getToken() == "/=") {
                        double d = expr(true);
                        if(d == 0) err("Divide by zero");
                        v /= d;
                    }
                    return v;
                    
                }
                    break;
                case TOKEN_OPERATOR: {
                    if(input.GetCurrent().getToken() == "-") {
                        return -prim(true);
                        
                    } else if (input.GetCurrent().getToken() == "(") {
                        auto e = expr(true);
                        if(input.GetCurrent().getToken() != ")") err("Expected )");
                        input.GetToken();
                        return e;
                    }
                }
                    break;
                default:
                    return 0;
            }
            
          
            if(input.GetCurrent().getToken() == ")")
                err("No argument");
            return 0;
        }
        
        double term(bool get) {
            double left = prim(get);
            while(1) {
                std::string temp=input.GetCurrent().getToken();
                Token_type tok_type = input.GetCurrent().getType();
                if(tok_type == TOKEN_CHAR || tok_type == TOKEN_DIGIT) {
                    err("Invalid type expected operator");
                }
                switch(tok_type) {
                     case TOKEN_OPERATOR: {
                        switch(temp[0]) {
                            case '*':
                                left *= prim(true);
                                break;
                            case '/':
                                if(auto d = prim(true)) {
                                    left /= d;
                                    break;
                                }
                                 err("Divide by Zero");
                                break;
                            default:
                                return left;
                        }
                        break;
                    default:
                        break;

                     }
                }
            }
            return 0;
        }
        
        double expr(bool get) {
            double left = term(get);
            while(1) {
                 switch(input.GetCurrent().getType()) {
                     case TOKEN_EOF:
                         throw lex::Scanner_EOF();
                         break;
                    case TOKEN_OPERATOR:
                    {
                        std::string temp=input.GetCurrent().getToken();
                        
                        if(temp == "++") err("No ++ right now\n");
                        if(temp == "--") err("No -- right now\n");
                        
                        switch(temp[0]) {
                            case '+':
                                left += term(true);
                                break;
                            case '-':
                                left -= term(true);
                                break;
                            default:
                                return left;
                        }
                        
                    }
                        break;
                    default:
                        return 0;
                }
            }
        }
    };

}

#endif








