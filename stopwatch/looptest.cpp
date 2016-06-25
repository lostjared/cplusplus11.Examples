#include<iostream>
#include<string>
#include<cstdlib>
#include<ctime>
#include"stopwatch.hpp"

const int arr_size = 9000;

int array[arr_size][arr_size];

void XFirst() {
    StopWatch<SystemClock> timer("Loop X First");
    for(unsigned int x = 0; x < arr_size; ++x) {
        for(unsigned int y = 0; y < arr_size; ++y) {
            array[x][y] = rand()%255;
        }
    }
    
    
}

void YFirst() {
    StopWatch<SystemClock> timer("Loop Y First");
    for(unsigned int y = 0; y < arr_size; ++y) {
        for(unsigned int x = 0; x < arr_size; ++x) {
            array[x][y] = rand()%255;
        }
    }
}

int main() {
    
    srand(static_cast<unsigned int>(time(0)));
    XFirst();
    YFirst();
    return 0;
}