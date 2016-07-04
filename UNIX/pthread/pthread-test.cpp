#include<iostream>
#include<pthread.h>
#include<unistd.h>


void *threadFunction(void *v) {
    for(unsigned int i = 0; i < 100; ++i)
    	std::cout << "Hello World\n";
    
    return 0;
    
}

int main() {
    std::cout << "pthread test\n";
    pthread_t id[4];
    for(unsigned int i = 0; i < 4; ++i) {
        pthread_create(&id[i], NULL, threadFunction, NULL); // run concurrently will out put at same time
    }
    
    for(unsigned int i = 0; i < 4; ++i) {
        pthread_join(id[i],NULL);
    }
    
    return 0;
}