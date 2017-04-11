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

int main() {
    bool active = true;
    interp::Code code;
    
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
                for(auto i = interp::lines.begin(); i != interp::lines.end(); ++i) {
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
                if(interp::saveLineSource(filename)) {
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
                if(interp::openLineSource(filename)) {
                    std::cout << "Loaded: " << filename << "\n";
                }
                continue;
            } else if(first_token == "clear") {
                if(!interp::lines.empty()) {
                    interp::lines.erase(interp::lines.begin(), interp::lines.end());
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
                for(unsigned int i = 0; i < interp::lines.size(); ++i) {
                    if(interp::lines[i].index == in) {
                        interp::lines.erase(interp::lines.begin()+i);
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
                for(unsigned int i = 0; i < interp::lines.size(); ++i) {
                    if(interp::lines[i].index == in) {
                        std::cout << interp::lines[i].index << " " << interp::lines[i].text << "\n";
                        found = true;
                        break;
                    }
                }
                if(found == false) {
                    std::cerr << "Index: " << in << " not found!\n";
                    continue;
                }
                continue;
            } else if(first_token == "convert") {
                code.clear();
                for(unsigned int i = 0; i < interp::lines.size(); ++i) {
                    if(procLine(interp::lines[i], code) == false)
                        std::cerr << "Line: " << interp::lines[i].index << " contains errors.\n";
                    
                }
                continue;
            }
            interp::inputText(v, input_line);
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
