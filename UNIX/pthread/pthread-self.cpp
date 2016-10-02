#include<iostream>
#include<unistd.h>
#include<pthread.h>
#include<errno.h>
#include<cstring>
#include<string>


void _error(const std::string &text);

pthread_t tid;

void *threadfunc(void *v) {
    std::cout << "Hello Thread World...\n";
    if(pthread_equal(tid, pthread_self())) {
        std::cout << "Yeah its me..\n";
    }
    return (void*) 100;
}


int main() {
    std::cout << "Hello World from main function..\n";
    int rt_val = 0;
    rt_val = pthread_create(&tid, 0, threadfunc, (void*)0);
   
    if(rt_val != 0)
        _error("pthread_create");
    
    void *return_value;
    rt_val = pthread_join(tid, &return_value);
    
    if(rt_val != 0)
        _error("pthread_join");
    
    if(((long)return_value) != 100)
        std::cout << "Something went wrong..\n";
    else
        std::cout << "Yeah everything is working okay..\n";
    
    return 0;
}

void _error(const std::string &text) {
    std::cerr << "Error: " << text << "\n";
    exit(EXIT_FAILURE);
}
