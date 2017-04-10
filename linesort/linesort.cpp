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
 
 */

#include<iostream>
#include<string>
#include<cstdlib>
#include<vector>
#include<algorithm>
#include<fstream>
#include "lexer.hpp"
#include<sstream>

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

void inputText(std::vector<lex::Token> &tokens, std::string text);
bool saveLineSource(const std::string &text);
bool openLineSource(const std::string &text);
void insertText(const TextLine &in);

std::vector<TextLine> lines;

bool saveLineSource(const std::string &text) {
    std::fstream file;
    file.open(text, std::ios::out);
    if(!file.is_open()) return false;
    for(unsigned int i = 0; i < lines.size(); ++i) {
        file << lines[i].index << " " << lines[i].text << "\n";
    }
    file.close();
    return true;
}

bool openLineSource(const std::string &text) {
    std::fstream file;
    file.open(text, std::ios::in);
    if(!file.is_open()) return false;
    if(!lines.empty()) {
        lines.erase(lines.begin(), lines.end());
    }
    while(!file.eof() && file) {
        std::string in;
        std::getline(file,in);
        if(in.length()==0) continue;
        std::vector<lex::Token> tokens;
        std::istringstream stream(in);
        lex::Scanner scan(stream);
        while(scan.valid()) {
            lex::Token token;
            scan >> token;
            tokens.push_back(token);
        }
        inputText(tokens, in);
    }
    file.close();
    return true;
}

void insertText(const TextLine &in) {
    for(unsigned int i = 0; i < lines.size(); ++i) {
        if(lines[i].index == in.index) {
            lines[i].text = in.text;
            return;
        }
    }
    lines.push_back(in);
    std::sort(lines.begin(), lines.end());
}

void inputText(std::vector<lex::Token> &tokens, std::string input_line) {
    if(tokens.size()>=2 && input_line.length()>0) {
        lex::Token_type num = tokens[0].getTokenType();
        if(num != lex::TOKEN_DIGIT) {
            std::cerr << "Requires line number before code.\n";
            return;
        }
        int value = atoi(tokens[0].getToken().c_str());
        std::string codetext;
        codetext = input_line.substr(input_line.find(tokens[0].getToken())+tokens[0].getToken().length()+1, input_line.length());
        TextLine in(value, codetext);
        insertText(in);
    } else {
        std::cerr << "Error invalid input.\n";
        return;
    }
}

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
            else if(first_token == "list") {
                for(auto i = lines.begin(); i != lines.end(); ++i) {
                    std::cout << i->index << ": " << i->text << "\n";
                }
                continue;
            } else if (first_token == "save" && v.size()>=2) {
                if(v[1].getTokenType() != lex::TOKEN_STRING) {
                    std::cerr << "Save requires string operand in quotes.\n";
                    continue;
                }
                std::string filename;
                filename = v[1].getToken();
                if(saveLineSource(filename)) {
                    std::cout << "Saved: " << filename << "\n";
                }
                continue;
            } else if(first_token == "open" && v.size()>=2) {
                if(v[1].getTokenType() != lex::TOKEN_STRING) {
                    std::cerr << "open requires string operand in quotes.\n";
                    continue;
                }
                std::string filename;
                filename = v[1].getToken();
                if(openLineSource(filename)) {
                    std::cout << "Loaded: " << filename << "\n";
                }
                continue;
            } else if(first_token == "clear") {
                if(!lines.empty()) {
                    lines.erase(lines.begin(), lines.end());
                }
                continue;
            } else if(first_token == "remove" && v.size() >= 2) {
                if(v[1].getTokenType() != lex::TOKEN_DIGIT) {
                    std::cerr << "remove requires line number.\n";
                    continue;
                }
                std::string index;
                index = v[1].getToken();
                int in = atoi(index.c_str());
                bool found = false;
                for(unsigned int i = 0; i < lines.size(); ++i) {
                    if(lines[i].index == in) {
                        lines.erase(lines.begin()+i);
                        found = true;
                        break;
                    }
                }
                if(found == true)
                    std::cout << "Line: " << in << " removed..\n";
                else
                    std::cerr << "Line: " << in << " not found..\n";
                
                continue;
            } else if(first_token == "display" && v.size() >= 2) {
                if(v[1].getTokenType() != lex::TOKEN_DIGIT) {
                    std::cerr << "display requires line number.\n";
                    continue;
                }
                std::string index;
                index = v[1].getToken();
                bool found = false;
                int in = atoi(index.c_str());
                for(unsigned int i = 0; i < lines.size(); ++i) {
                    if(lines[i].index == in) {
                        std::cout << lines[i].index << " " << lines[i].text << "\n";
                        found = true;
                        break;
                    }
                }
                if(found == false) {
                    std::cerr << "Index: " << in << " not found!\n";
                    continue;
                }
                continue;
            }
        	inputText(v, input_line);
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
