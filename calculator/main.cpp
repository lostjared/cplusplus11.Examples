//  Created by Jared Bruni on 7/14/13.

#include<iostream>
#include<iomanip>
#include<sstream>
#include<cstdlib>
#include<ctime>
#include<cmath>
#include "lexer.h"


namespace driver {

    /* temporary */
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
    
    /* end temporary */
    
    void grabInput() {
        std::cout << "=)> ";
        std::string s;
        std::getline(std::cin, s);
        
        if(!std::cin) return;
        
        if(s.find(";") == std::string::npos) {
            std::cerr << "Error missing semi-colon\n";
            return grabInput();
        }
        if(s.length()==0) return;
        std::istringstream stream(s);
        lex::Parser pscan(stream, variables, functions);
        if(pscan.eval()) {
            for (auto &s : driver::variables) {
                std::cout << std::setw(10) << s.first << " " << std::setw(10) << s.second << "\n";
            }
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
}

int main(int argc, char **argv) {
    try {
        driver::initFunctions();
        std::cout << "Enter Expression: \n";

        while(!std::cin.eof()) {
            driver::grabInput();
        }
    }
    catch(std::exception &e) {
        std::cerr << e.what() << "\n";
    }
    catch(lex::Scanner_EOF) {
        std::cout << "end of file.\n";
    }
    catch(lex::Exit_Exception) {
        std::cout << "Exit called, Quiting...\n";
        return 0;
    }
    return 0;
}
