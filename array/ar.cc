/*
 
 written by Jared Bruni
 http://lostsidedead.com
 
 example of std::array
 
*/




#include<iostream>
#include<array>
#include<cstdlib>
#include<ctime>

template<typename T, int N>
T average(std::array<T, N> &a) {
    T t{};
    for(int i = 0; i < N; ++i) {
        t += a[i];
    }
    return t/N;
}

int main(int argc, char **argv) {

    // seed the random number generator
    std::srand(static_cast<unsigned int>(std::time(0)));
    
    std::array<float, 4> arr;
    arr[0]=255;
    arr[1]=1024;
    arr[2]=2048;
    arr[3]=4092;

    float avg = average<float, 4>(arr);
    std::cout << avg << "\n";

    // multi dimensional array
    
    std::array<std::array<float, 4>, 4> grid;
    
    for(signed int i = 0; i < 4; ++i) {
        for(signed int z = 0; z < 4; ++z) {
            grid[i][z] = std::rand()%100; // set element to random number
        }
    }
    
    for(signed int q = 0; q < 4; ++q) {
        float avg = average<float, 4>(grid[q]); // average
        std::cout << "average is: " << avg << "\n";
    }
    
    return 0;
}