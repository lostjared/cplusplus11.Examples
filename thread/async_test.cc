
/*
 
 creates a few tasks, and will output which one finishes first.
 
 written by Jared Bruni
 http://lostsidedead.com
*/

#include<iostream>
#include<string>
#include<thread>
#include<vector>
#include<future>
#include<chrono>

std::string demoTask(int z) {
    for(int i = 0; i < 1000; ++i) {
        for(int q = 0; q < 3; ++q) {
            std::this_thread::sleep_for(std::chrono::microseconds{10});
        }
    }
    switch(z) {
        case 0:
            return "Zero\n";
        case 1:
            return "One\n";
        case 2:
            return "Two\n";
    }
    return "";
}

template<typename T>
int wait_for_any(std::vector<std::future<T>> &v, std::chrono::steady_clock::duration d) {
    
    using namespace std;
    using namespace std::chrono;
    
    while(1) {
        for(unsigned int i = 0; i != v.size(); ++i) {
            if(!v[i].valid()) continue;
            switch(v[i].wait_for(seconds{0})) {
                case future_status::ready:
                return i;
                break;
            case future_status::timeout:
                break;
            case future_status::deferred:
                throw runtime_error("Wait deferred\n");
                break;
            }
        }
        this_thread::sleep_for(d);
    }
    return 0;
}

int main(int argc, char **argv) {
    
    std::vector<std::future<std::string>> v;

    for(int i = 0; i < 3; ++i) {
       v.push_back(async(demoTask, i));
    }

    int first = wait_for_any(v,std::chrono::microseconds{10});
   
    auto temp = v[first].get();
    if(temp.length() > 0) {
        std::cout << temp << " finished first.\n";
    }
    
    return 0;
}
