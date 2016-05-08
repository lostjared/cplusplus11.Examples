/* test of std::future */

#include<iostream>
#include<future>
#include<thread>
#include<random>
#include<ctime>

int printOut(char c) {
    std::default_random_engine dre(static_cast<int>(std::time(0)));
    unsigned int num = dre()%100;
    for(unsigned int i = 0; i < num; ++i) {
        std::cout.put(c).flush();
    }
    return num;
}

int main(int argc, char **argv) {
    std::future<int> printNum;
    std::cout << "+ for thread1\nx for thread2\n";
    printNum = std::async(printOut, '+');
    int total_value = printOut('x') + printNum.get();
    std::cout << "\nTotal value: " << total_value << "\n";
    return 0;
}