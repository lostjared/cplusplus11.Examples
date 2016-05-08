#include<iostream>
#include<algorithm>
#include<vector>
#include<string>

int main() {
    std::vector<std::string> vec;
    std::cout << "Enter multiple strings use quit to terminate\n";
    std::string value;
    do {
        std::cin >> value;
        vec.push_back(value);
    } while(value!="quit");
    
    auto contains = std::find_if(vec.begin(), vec.end(), [](std::string text) {
        return (text == "hello");
    });
    
    if(*contains == "hello") {
        std::cout << "You entered hello\n";
    } else {
        std::cout << "You didn't enter hello\n";
    }
    return 0;
}