/* 
 written by Jared Bruni
 http://lostsidedead.com
*/

#include<iostream>
#include<cctype>

template<typename Iter>
void LowerCase(Iter start, Iter stop) {
    for(Iter i = start; i != stop; ++i) {
        *i = tolower(*i);
    }
}

template<typename Iter, typename F>
void ApplyFunction(Iter start, Iter stop, F f) {
    for(Iter i = start; i != stop; ++i) {
        *i = f(*i);
    }
}

int main(int argc, char **argv) {
    
    
    std::cout << "Enter string: ";
    std::string s;
    std::cin >> s;
    
    LowerCase(s.begin(), s.end());
    std::cout << "Lowercased: " << s << "\n";
    
    ApplyFunction(s.begin(), s.end(), [](char c) { return toupper(c); });
    
    std::cout << "Uppercased: " << s << "\n";
    
    return 0;
}