/*
 
 Line Sort - Practice Project
 written by Jared Bruni
 http://lostsidedead.com
 
 Enter digit then text like on old 8 bit machines
 
 > 10 hey
 > 20 test
 > 30 here
 
 enter list to display
 
 > list

 > quit
 
 to exit
 
 other commands:
 
 > save filename
 > open filename
 > clear
 > remove index
 > dispaly index
 > convert
 
 */

#include"code.hpp"
#include"function.hpp"
#include<unordered_map>

typedef void (*tokenFunc)(std::vector<lex::Token> &tokens);

struct Command {
    int args;
    tokenFunc func;
    Command() = default;
    Command(tokenFunc ifunc, int iargs) {
        args = iargs;
        func = ifunc;
    }
};

std::unordered_map<std::string, Command> function_map = {
    { "convert",Command(token::token_Convert, 0) },
    { "list",Command(token::token_List, 0) },
    { "save",Command(token::token_Save, 2) },
    { "open",Command(token::token_Open, 2) },
    { "clear",Command(token::token_Clear, 0) },
    { "remove",Command(token::token_Remove, 1) },
    {"display",Command(token::token_Display, 1) }
};

int main() {
    bool active = true;
    while(active) {
        try {
            std::cout << "> ";
            std::string input_line;
            std::getline(std::cin, input_line);
            std::istringstream stream(input_line);
            lex::Scanner scan(stream);
            std::vector<lex::Token> v;
            while(scan.valid()) {
                lex::Token s;
                scan >> s;
                v.push_back(s);
            }
            if(v.size()==0) continue;
            std::string first_token;
            first_token = v[0].getToken();
            if(first_token == "quit") break;
            auto rt = function_map.find(first_token);
            if(rt == function_map.end()) {
                interp::inputText(v, input_line);
                continue;
            }
            
            int token_count = v.size()-1;
            
            if(token_count == rt->second.args) rt->second.func(v);
            else {
                std::cout << "Error " << first_token << " requires: " << rt->second.args << " arguments. You gave " << token_count << "\n";
            }
        }
        catch(lex::Scanner_EOF) {
            
        }
        catch(lex::Scanner_Error) {
            std::cerr << "Scanner Error has occured.\n";
        }
        catch(std::exception &e) {
            std::cerr << "System Exception thrown: " << e.what() << "\n";
        }
        catch(...) {
            std::cerr << "Unknown Exception thrown...\n";
        }
    }
    return EXIT_SUCCESS;
}
