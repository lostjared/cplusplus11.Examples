/* deatch test
  written by Jared Bruni
 
 http://lostsidedead.com
 
*/

#include<iostream>
#include<thread>
#include<mutex>
#include<random>

std::mutex m;

void background_Thread() {
    std::default_random_engine dre(static_cast<int>(time(0)));
    std::this_thread::sleep_for(std::chrono::seconds(dre()%2));
    std::lock_guard<std::mutex> lock(m);
    std::cout << "Woke up" << "\n";
}

int main(int argc, char **argv) {
    
    for(unsigned int i = 0; i < 10; ++i) {
        std::thread t(background_Thread);
        t.detach();
    }
    
    std::this_thread::sleep_for(std::chrono::seconds(4));
    std::cout << "Exiting...\n";
    
    return 0;
}
