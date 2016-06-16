/* String Test using Stop Watch template class */

#include<iostream>
#include<string>
#include<cstdlib>
#include<fstream>
#include"stopwatch.hpp"

// unoptimized function
std::string unop_RemoveSpace(std::string search) {
    std::string result;
    for(size_t i = 0; i < search.length(); ++i) {
        if(search[i] != ' ') {
            result = result + search[i];
        }
    }
    return result;
}

// optimized function
void op_RemoveSpace(std::string &result, const std::string &search) {
    result.clear();
    result.reserve(search.length());
    for(auto i=search.begin(), stop=search.end(); i != stop; ++i) {
        if(*i != ' ') result += *i;
    }
}

void testRemoveSpace(std::string s) {
    unsigned long timedValues[100];
    for(unsigned int i = 0; i < 100; ++i) {
        StopWatch<HighResolutionClock> timer_clock("Unoptimized Remove Space");
        unop_RemoveSpace(s);
        timedValues[i] = timer_clock.TimePassed();
    }
    double average = 0;
    for(unsigned int i = 0; i < 100; ++i) {
        average += timedValues[i];
    }
    average /= 100;
    std::cout << "Average time for unoptimized function call: " << average << " nanoseconds\n";
}

void op_testRemoveSpace(std::string s) {
    unsigned long timedValues[100];
    std::string result;
    for(unsigned int i = 0; i < 100; ++i) {
        StopWatch<HighResolutionClock> timer_clock("Optimized Remove Space");
        op_RemoveSpace(result, s);
        timedValues[i] = timer_clock.TimePassed();
    }
    double average = 0;
    for(unsigned int i = 0; i < 100; ++i) {
        average += timedValues[i];
    }
    average /= 100;
    std::cout << "Average time for optimized function call: " << average << " nanoseconds\n";
}


int main() {
    std::fstream file;
    file.open("string-test.cpp", std::ios::in|std::ios::binary);
    if(!file.is_open()) {
        std::cerr << "Could not open file string-test.cpp\n";
        exit(0);
    }
    file.seekg(0, std::ios::end);
    size_t len = file.tellg();
    file.seekg(0, std::ios::beg);
    char *value = new char[len+1];
    file.read(value, len);
    std::string temp(value);
    delete [] value;
    file.close();
    
    testRemoveSpace(temp);
    op_testRemoveSpace(temp);
    return 0;
}