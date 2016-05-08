
#include<iostream>
#include<random>
#include<ctime>
#include<vector>
#include<string>
#include<sstream>

template<typename T>
void printVector(std::vector<T> &v) {
    std::cout << "[ ";
    for(auto &i : v) {
        std::cout << i << " ";
    }
    std::cout << "]\n";
}

template<typename T>
T addup(std::vector<T> &v) {
    unsigned int i = 0;
    T total{};
    for(i = 0; i < v.size(); ++i)
        total += v[i];
    
    return total;
}

template<typename T>
std::string vectorToString(std::vector<T> &v) {
    std::ostringstream stream;
    stream << "[ ";
    for(auto &i : v)
        stream << v[i] << " ";
    
    stream << "]";
    return stream.str();
}

int main(int argc, char **argv) {
    unsigned int i = 0;
    std::vector<int> numbers;
    std::default_random_engine dre(static_cast<int>(std::time(0)));;
    for(i = 0; i < 25; ++i) {
        numbers.push_back(i);
    }
    std::cout << "Vector: \n";
    printVector(numbers);
    std::shuffle(numbers.begin(), numbers.end(), dre);
    std::cout << "After Shuffle: \n";
    printVector(numbers);
    std::sort(numbers.begin(), numbers.end());
    std::cout << "After sort: \n";
    printVector(numbers);
    int total = addup(numbers);
    std::cout << "All items added together: " << total << "\n";
    
    std::string value = vectorToString(numbers);
    std::cout << "Vector to string: " << value << "\n";
    
    return 0;
}

