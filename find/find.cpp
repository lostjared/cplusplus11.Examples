#include<iostream>
#include<vector>
#include<algorithm>

std::vector<int> values;


int main() {

    for(unsigned int i = 0; i < 500; ++i) {
        values.push_back(rand()%100);
    }
    
    auto it = std::find(values.begin(), values.end(), 57);
    
    if(it != values.end()) {
        std::cout << "Found 57 in values\n";
    }
    else {
        std::cout << "Did not find 57..\n";
    }
    
    std::string text;
    std::cin >> text;
    
    if(text.find("e") != -1) {
        std::cout << "You typed a e.\n";
    }
    else {
        std::cout << "You didn't type a e.\n";
    }
    
    return 0;
}
