/*
 
 written by Jared Bruni
 http://lostsidedead.com

 */


#include<iostream>
#include<vector>
#include<unordered_map>
#include<cctype>
#include<cstdlib>
#include<string>
#include<algorithm>

std::string tolower(std::string temp) {
    std::string t;
    for(auto i = temp.begin(); i != temp.end(); ++i)
        t += std::tolower(*i);
    return t;
}

template<typename Iter>
void EchoAll(Iter start, Iter stop) {
    for(Iter i=start; i!=stop; ++i) {
        std::cout << "Echo: " << *i << "\n";
    }
}

template<typename Iter>
void EchoAll2(Iter i, Iter stop) {
    std::cout << "Echo #2: " << *i << "\n";
    ++i;
    if(i != stop) EchoAll2(i, stop); // use recursion
}

template<typename C>
auto begin_test(C &c) -> decltype(c.begin()) { return c.begin(); }

template<typename C>
auto end_test(C &c) -> decltype(c.end()) { return c.end(); }

template<typename Iter>
bool search_lcase(Iter start, Iter stop, std::string text) {
    for(Iter i = start; i != stop; ++i)
        if(tolower(*i) == tolower(text)) return true;
    
    return false;
}

template<typename C, typename T>
void PushList(C &c, std::initializer_list<T> t) {
    for(auto i = t.begin(); i != t.end(); ++i) {
        c.push_back(*i);
    }
}

int main(int argc, char **argv) {
    std::vector<std::string> v{"String One", "String Two", "String Three", "Temporary ", "Value 1"};
    EchoAll(v.begin(), v.end()); // Print forward
    EchoAll(v.rbegin(), v.rend()); // Print backwards
    std::sort(v.begin(), v.end());
    EchoAll2(v.begin(), v.end());
    PushList(v, {"Added this string", "And this one", "also this one"});
    std::sort(v.begin(), v.end());
    for(auto i = begin_test(v); i != end_test(v); ++i) {
        std::cout << "Value is: " << *i << "\n";
    }
    if(search_lcase(v.begin(), v.end(), "string three") == true) {
        std::cout << "Search true.\n";
    }
    if(search_lcase(v.begin(), v.end(), "ABC") == false) {
        std::cout << "Not found.\n";
    }
    return 0;
}