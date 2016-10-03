/* 

Adapted from "The Linux Programming Interface"
Listing 32-2 page 678-679
 
*/

#include<iostream>
#include<string>
#include<pthread.h>
#include<unistd.h>

pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;
int change = 0;

void error(const std::string &text);

void cleanUp(void *i) {
    int rt_val;
    std::cout << "Cleanup freeing block: " << (long)i << "\n";
    free(i);
    std::cout << "Cleanup unlocking mutex..\n";
    rt_val = pthread_mutex_unlock(&mut);
    if(rt_val != 0)
        error("pthread_mutex_unlock");
}

void *thread_func(void *i) {
    int rt_val;
    void *buffer = NULL;
    
    buffer = malloc(1000);
    std::cout << "Allocated Memory at: " << (long)buffer << "\n";
    rt_val = pthread_mutex_lock(&mut);
    if(rt_val != 0)
        error("pthread_mutex_lock");
    
    pthread_cleanup_push(cleanUp, buffer);
    
    while(change == 0) {
        rt_val = pthread_cond_wait(&cond, &mut);
        if(rt_val != 0)
            error("pthread_cond_wait");
    }
    std::cout << "Thread wait complete..\n";
    pthread_cleanup_pop(1);
    return NULL;
}

int main(int argc, char **argv) {
    
    pthread_t id;
    void *return_buffer = NULL;
    int rt_val;
   
    std::cout << "Sleeping for 3 seconds..\n";
    
    rt_val = pthread_create(&id, 0, thread_func, 0);
    if(rt_val != 0)
        error("pthread_create");
    
    sleep(3);
    
    if(argc == 1) {
        std::cout << "Canceling thread..\n";
        rt_val = pthread_cancel(id);
        if(rt_val != 0)
            error("pthread_cancel");
    } else {
        std::cout << "Signaling thread..\n";
        change = 1;
        rt_val = pthread_cond_signal(&cond);
        if(rt_val != 0)
            error("pthread_cond_signal");
    }
    
    rt_val = pthread_join(id,&return_buffer);
    if(rt_val != 0)
        error("pthread_join");
    
    if(return_buffer == PTHREAD_CANCELED)
        std::cout << "Thread was canceled..\n";
    else
        std::cout << "Thread terminated normally..\n";
    
    return 0;
}

void error(const std::string &text) {
    std::cerr << "Error: " << text << "\n";
    exit(EXIT_FAILURE);
}
