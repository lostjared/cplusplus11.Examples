
// Custom search to see if string contains possible code.
// Then another search with regex.
//  Created by Jared Bruni on 7/14/13.

#include<iostream>
#include<regex>


// Custom search without Regex

class SearchString {
public:
    SearchString(std::string ctxt, std::initializer_list<std::string> csearch) : txt(ctxt), search(csearch) {}
    bool procSearch() {
        std::string temp_text=lower(txt);
        for(auto &s : search) {
            if(temp_text.find(lower(s)) != -1){
                std::cout << "Token found: " << s << "\n";
                return true;
            }
        }
        return false;
    }
    
    std::string lower(std::string text) {
        std::string temp;
        auto l = text.length();
        
        for(unsigned int i = 0; i < l; ++i)
            temp += tolower(text[i]);
        return temp;
    }
    
    bool operator()() {
        return procSearch();
    }
protected:
    std::string txt;
    std::initializer_list<std::string> search;

};

// output match info

void output(std::ostream &out, bool b) {
    if(b) out << "Successful Match\n";
    else out << "No match\n";
}

int main(int argc, char **argv) {
    
    try {
        // search with Regex (better)
        
        std::regex exp1("<.*>.*</.*>");
        bool isTag = std::regex_match("<tag>value</tag>", exp1);
        output(std::cout, isTag);
        std::string test;
        std::cout << "Enter string to test match (enter any <whatever>test</whatever>: ";
        std::getline(std::cin, test);
        bool isTag2 = std::regex_match(test, exp1);
        output(std::cout, isTag2);
        
        std::cout << "Enter test string to see if it contains any instance of the initalizer list\n";
        std::getline(std::cin, test);
        // search with Custom search
        
        SearchString search(test, {"var", "char", "String", "int", "string", "for", "if", "do", "while", "exit", ">>", "<<", "class", "protected", "public", "{", "}", "(", ")", ";", "-", ":", "&", "|", "!", "[", "]"});
        output(std::cout, search());
        
        
    } catch(std::exception &e) {
        std::cerr << "Exception: " << e.what() << "\n";
    } catch(...) {
        std::cerr << "Unknown Exception:  \n";
    }
    return 0;
}