//
//
//  Created by Jared Bruni on 7/9/13.
//

#include<iostream>
#include<thread>
#include<mutex>

std::mutex mut;

class Background {
    int id;
public:
    Background(int id) {
        this->id = id;
    }
    void operator()() {
        for(int i = 0; i < 100; ++i) {
            mut.lock();
            std::cout << "Background thread: " << id << "\n";
            mut.unlock();
        }
    }
};


int main(int argc, char **argv)
{
    std::cout << "start.\n";
    Background back(0), back2(1);
    std::thread t(back);
    std::thread t2(back2);

    std::thread lamb_thread([]() {
    
        for(int i = 0; i < 100; ++i) {
            mut.lock();
            std::cout << "Here\n";
            mut.unlock();
        }
    
    });
    
    t.join();
    t2.join();
    lamb_thread.join();
    
    return 0;
}

