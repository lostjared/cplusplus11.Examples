/* C++11 atomic example
   written by Jared Bruni
   http://lostsidedead.com
*/

#include<iostream>
#include<thread>
#include<unistd.h>
#include<atomic>


std::atomic<int> value; // value can be used by both threads without worry

void thread1() {
    // testing value
    while(value != 1) {
        std::cout << "Checking Values...\n";
    }
    std::cout << "value changed.\n";
}

void thread2() {
    sleep(2);
    // set the value
    value = 1;
}


int main(int argc, char **argv) {

    std::cout << "adding threads..\n";
    // creating the threads
    std::thread t1(thread1);
    std::thread t2(thread2);
    
    
    // wait for the threads to finish before exiting
    t1.join();
    t2.join();
    return 0;
}
