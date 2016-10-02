#include<iostream>
#include<unistd.h>
#include<pthread.h>

pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;

const int MAX_THREADS = 10;
const int MAX_ITERATIONS = 100;


void *thread_function(void *arg) {
    long id = (long)arg;
    for(unsigned int i = 0; i < MAX_ITERATIONS; ++i) {
        pthread_mutex_lock(&mut);
        std::cout << "in thread index: " << id << "\n";
        pthread_mutex_unlock(&mut);
    }
    return 0;
}


int main() {
    std::cout << "Starting threads..\n";
    pthread_t t_id[MAX_THREADS];
    
    for(long i = 0; i < MAX_THREADS; ++i) {
        pthread_create(&t_id[i], 0, thread_function, (void*)i);
    }
    
    for(int i = 0; i < MAX_THREADS; ++i) {
        pthread_join(t_id[i], 0);
    }
    
    return EXIT_SUCCESS;
}
