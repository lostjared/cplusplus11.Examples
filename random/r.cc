// example of new random in C++11

#include<iostream>
#include<random>
#include<ctime>

int main(int argc, char **argv) {
    
    unsigned int i = 0;
    std::default_random_engine dre(static_cast<int>(std::time(0)));
    
    for(i = 0; i < 10; ++i) {
        std::cout << "Random number 0-10: " << dre()%10 << "\n";
    }
    
    std::uniform_int_distribution<int> ui(0, 10);
    for(i = 0; i < 10; ++i) {
        std::cout << "Uniform: " << ui(dre) << "\n";
    }

    return 0;
}