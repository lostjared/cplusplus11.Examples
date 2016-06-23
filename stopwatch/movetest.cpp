#include<iostream>
#include<string>
#include<vector>
#include"stopwatch.hpp"


void move_Test(std::vector<int> &&v) {
    StopWatch<SystemClock> clock("move");
    std::vector<int> mv;
	mv = std::move(v);
}

void copy_Test(std::vector<int> &v) {
    StopWatch<SystemClock> clock("copy");
    std::vector<int> mv;
    mv = v;
}


int main() {
    std::vector<int> test_vector;
    for(unsigned int i = 0; i < 999999; ++i) test_vector.push_back(i);
    copy_Test(test_vector);
    move_Test(std::move(test_vector));
    
    return 0;
}