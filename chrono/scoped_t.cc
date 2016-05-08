/*
 written by Jared Bruni
 http://lostsidedead.com
*/

#include<iostream>
#include<chrono>


class ScopedTime {
public:
    std::chrono::high_resolution_clock::time_point time_start;
    ScopedTime();
    ~ScopedTime();
};

ScopedTime::ScopedTime(){
    time_start = std::chrono::high_resolution_clock::now();
}

ScopedTime::~ScopedTime() {
    auto now = std::chrono::high_resolution_clock::now();
    std::cout << "Object was alive for : " << std::chrono::duration_cast<std::chrono::nanoseconds>(now-time_start).count() << " nanoseconds\n";
}

int main(int argc, char **argv) {
    
    // lets see how long these loops take.
    
    ScopedTime value_wait;
    for(unsigned int i = 0; i < 100; ++i) {
        for(unsigned int i = 0; i < 100; ++i) {
            ScopedTime inner_loop;
            for(unsigned z = 0; z < 10000; ++z) { }
        }
    }
    
    return 0;
}