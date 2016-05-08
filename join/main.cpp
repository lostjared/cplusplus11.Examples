#include"join.hpp"
#include<iostream>
#include<vector>
#include<array>

std::vector<std::string> values { "one", "two", "three" };
std::array<std::string,4> values_array { "C", "C++", "Objective-C", "Objective-C++" };

int main() {
    
    std::string value = join(values, ",");
    std::cout << value << "\n";
    std::string joined_string = join(values_array,",");
    std::cout << joined_string << "\n";
    return 0;
}