#include<iostream>
#include<string>
#include<vector>
#include<cstdlib>
#include<ctime>

#include"stopwatch.hpp"



void concat_Values(std::vector<int> &v) {
    unsigned long value = 0;
    for(auto &i : v) {
        value += i;
    }
    std::cout << "Value is: " << value << "\n";
}


void copy_Test(std::vector<int> &v) {
    StopWatch<SystemClock> clock("copy");
    std::vector<int> mv;
    mv = v;
    concat_Values(mv);
}


void move_Test(std::vector<int> &&v) {
    StopWatch<SystemClock> clock("move");
    std::vector<int> mv;
    mv = std::move(v);
    concat_Values(mv);
}



int main() {
    
    
    std::srand(static_cast<unsigned int>(std::time(0)));
    
    std::vector<int> test_vector;
    for(unsigned int i = 0; i < 999999; ++i) test_vector.push_back(rand()%255);
    
    copy_Test(test_vector);
    move_Test(std::move(test_vector));
    
    return 0;
}