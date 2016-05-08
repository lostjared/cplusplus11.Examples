#include<iostream>
#include<random>
#include<vector>
#include<ctime>

void printVector(std::vector<int> &v) {
    std::cout << "[ ";
    for(auto &i : v) {
        
        std::cout << i << " ";
    }
    std::cout << " ]\n";
}

int main(int argc, char **argv) {
    
    std::default_random_engine dre(static_cast<int>(std::time(0)));
    unsigned int i = 0;
    std::vector<int> values;
    
    
    for(i = 0; i < 25; ++i)
        values.push_back(dre()%25);
    
    std::cout << "Value before shuffle: \n";
    printVector(values);
    std::cout << "Value after shuffle:\n ";
    std::shuffle(values.begin(), values.end(), dre);
    printVector(values);
    
    return 0;
}