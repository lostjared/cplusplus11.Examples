#include<iostream>
#include<string>
#include<vector>
#include<thread>
#include<mutex>

std::mutex lmutex;

class ThreadObject {
public:
    ThreadObject(std::string thread_name) : name(thread_name) {}
    void operator()() {
        for(unsigned int i = 0; i < 100; ++i) {
            lmutex.lock();
            std::cout << name << ": " << i << "\n";
            lmutex.unlock();
        }
    }
private:
    std::string name;
};

int main() {
    ThreadObject thread1("thread one"), thread2 ("thread two"), thread3("thread three");
    std::thread t1(thread1), t2(thread2), t3(thread3);
    t1.join();
    t2.join();
    t3.join();
    return 0;
}
