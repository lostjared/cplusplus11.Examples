#include<iostream>
#include<set>
#include<string>

int main(int argc, char **argv) {
    
    std::cout << "input a series of integers terminate the loop by entering 0\n";
    // insert into set
    
    std::set<int> input_values;
    int value;
    
    do {
    
        std::cin >> value;
        input_values.insert(value);
        
    } while(value != 0);
    
    
    // display the set
    
    for(auto &i : input_values) {
        std::cout << i << "\n";
    }
    
    std::set<std::string, std::greater<std::string>> s1;
    std::set<std::string, std::less<std::string>> s2;
    std::string input_text;
    
    std::cout << "Input a series of strings quit to terminate\n";
    
    do {
        
        std::cin >> input_text;
        s1.insert(input_text);
        s2.insert(input_text);
        
    } while(input_text != "quit");
    
    std::cout << "Print greater: \n";
    
    for(auto &i : s1) {
        std::cout << i << "\n";
    }
    
    std::cout << "Print less: \n";
    
    for(auto &i : s2) {
        std::cout << i << "\n";
    }
    
    return 0;
}