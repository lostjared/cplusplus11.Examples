#include<iostream>
#include<pthread.h>

pthread_once_t onetime = PTHREAD_ONCE_INIT;
pthread_key_t func_key;

void error(const std::string &text);

void destructor(void *ptr) {
    std::cout << "Released pointer..\n";
    free(ptr);
}

void createKey() {
    int rt_val;
    
    rt_val = pthread_key_create(&func_key, destructor);
    
    if(rt_val != 0)
        error("pthread_key_create");
}

char *returnString(unsigned int size) {
    char *str;
    int rt_val;
    
    rt_val = pthread_once(&onetime, createKey);
    if(rt_val != 0)
        error("pthread_once");
    
    str = (char*) pthread_getspecific(func_key);
    if(str == NULL) {
        str = (char*) malloc(size);
        if(str == NULL)
            error("malloc");
        rt_val = pthread_setspecific(func_key, str);
        if(rt_val != 0)
            error("pthread_setspecific");
    }
    snprintf(str, size, "Hey this is a test string");
    return str;
}

pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;

void *thread_func(void *i) {
    char *ptr = returnString(100);
    int rt_val;
    
    rt_val = pthread_mutex_lock(&mut);
    
    if(rt_val != 0)
        error("pthread_mutex_lock");
    
    std::cout << ptr << "\n";
    
    rt_val = pthread_mutex_unlock(&mut);
    
    if(rt_val != 0)
        error("pthread_mutex_unlock");

    return 0;
}

int main() {
    
    pthread_t threads[10];
    unsigned int i = 0;
    
    for(i = 0; i < 10; ++i)
        pthread_create(&threads[i], 0, thread_func, 0);
    
    for(i = 0; i < 10; ++i)
        pthread_join(threads[i], 0);
    
    return 0;
}

void error(const std::string &text) {
    std::cerr << "Error: " << text << "\n";
    exit(EXIT_FAILURE);
}
