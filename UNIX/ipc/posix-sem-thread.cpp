#include<iostream>
#include<unistd.h>
#include<semaphore.h>
#include<cstring>
#include<errno.h>
#include<pthread.h>
#include<fcntl.h>

sem_t s;
void error(const std::string &text);

void *tfunction(void *v) {
    
    for(unsigned int i = 0; i < 1000; ++i) {
        
        if(sem_wait(&s) == -1)
            error("sem_wait");
        
        std::cout << "In loop: " << i << " " << (unsigned long)v << "\n";
       
        if(sem_post(&s) == -1)
            error("sem_post");
    }
    
    return 0;
}


int main(int argc, char **argv) {
    if(sem_init(&s, 0, 1) == -1) {
        std::cerr << "Error initializing semaphore: " << strerror(errno) << "\n";
        exit(EXIT_FAILURE);
    }
    pthread_t thread1, thread2;
    int rt;
    
    rt = pthread_create(&thread1, 0, tfunction, (void*)1);
    if(rt != 0)
        error("pthread_create");
    
    rt = pthread_create(&thread2, 0, tfunction, (void*)2);
    if(rt != 0)
        error("pthread_create");
    
    rt = pthread_join(thread1, 0);
    if(rt != 0)
        error("pthread_join");
    
    rt = pthread_join(thread2, 0);
    if(rt != 0)
        error("pthread_join");
    
    return EXIT_SUCCESS;
}

void error(const std::string &text) {
    std::cerr << "Error .. " << text << "\n";
    exit(EXIT_FAILURE);
}
