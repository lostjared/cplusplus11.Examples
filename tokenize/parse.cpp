#include<iostream>
#include<string>
#include<sstream>
#include<ctime>
#include<cmath>
#include"lexer.hpp"

std::unordered_map<std::string, double> variables;
std::unordered_map<std::string, lex::Func> functions;


double val_sqrt(double d) { return sqrtf(d); }
double val_abs(double d) { return abs(static_cast<int>(d)); }
double val_print(double d) {
    std::cout << "value of variable: " << d << "\n";
    return d;
}
double val_cosf(double d) { return cosf(d); }
double val_sinf(double d) { return sinf(d); }
double val_log(double d) { return logf(d); }
double val_tan(double d) { return tanf(d); }
double val_rand(double d) { return std::rand()%static_cast<int>(d); }
double val_exit(double d) {
    throw lex::Exit_Exception();
    return 0;
}

void add_func(std::initializer_list<lex::Func> lst) {
    for(auto &i : lst) {
        functions[i.name] = i;
    }
}

void initFunctions() {
    std::srand(static_cast<unsigned int>(std::time(0)));
    add_func({
        {"sqrt",val_sqrt}, {"abs",val_abs},
        {"print",val_print}, {"cos",val_cosf},
        {"sin",val_sinf}, {"tan",val_tan},
        {"log",val_log}, {"exit",val_exit},
        {"rand",val_rand}
    });
}


void outputToken(std::ostream &out, const lex::Token &token) {
    if(token.getToken() == "quit") {
        out << "Quit token read from stream exiting...\n";
        exit(0);
    }
    
    if(!token.isKeyword()) {
        out << "Token: [" << token.getToken() << "] of Type: [" << token.getType() << "]\n";
    }
    else {
        out << "Token: [" << token.getToken() << "] of Type: [Keyword]\n";
    }
}
int main() {

    initFunctions();
    bool active = true;
    while(active == true) {
        try {
            std::string line;
            std::cout << "Input Text: ";
            std::getline(std::cin, line);
            std::istringstream input(line);
            lex::Parser parser(input, variables, functions);
            parser.eval();
            parser.print();
            
        }
        catch(lex::Scanner_EOF) {
            std::cerr << "Scanner End of File.\n";
            
        }
        catch(lex::Scanner_Error) {
            std::cerr << "Scanner Error..\n";
        }
        catch(lex::Exit_Exception) {
            std::cout << "Exiting...\n";
            exit(0);
        }
    }
    return 0;
}