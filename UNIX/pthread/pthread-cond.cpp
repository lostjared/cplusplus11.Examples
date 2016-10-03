/* Adapted from "the Linux Programming Interface"
   Listing 30-4 on Page 649-651
*/

#include<iostream>
#include<unistd.h>
#include<pthread.h>
#include<memory>
#include<string>
#include<ctime>
#include<sys/time.h>
#include<cstdlib>


void error(const std::string &s);

pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t output_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;


int total_threads = 0;
int num_t = 0;
int num_j = 0;

enum STATE { ALIVE, TERM, JOINED };

class ThreadInfo {
public:
    ThreadInfo() : info(nullptr) {
        
    }
    ThreadInfo(unsigned int num) {
        info = new Info[num];
    }
    
    ~ThreadInfo() {
        if(info != nullptr) delete [] info;
    }
    
    void setInfo(unsigned int index, STATE s, pthread_t i, int sl) {
        info[index].state = s ;
        info[index].id = i;
        info[index].sleeptime = sl;
    }
    
    STATE &State(unsigned int index) const { return info[index].state; }
    pthread_t getId(unsigned int index) const { return info[index].id; }
    int getSleep(unsigned int index) const { return info[index].sleeptime; }
private:
    
    struct Info {
        STATE state;
        pthread_t id;
        int sleeptime;
    };
    
    Info *info;
};

std::unique_ptr<ThreadInfo> threads;

void *thread_func(void *arg) {
    long i = (long) arg;
    
    int rt_val;
    sleep(threads->getSleep(i));
    
    rt_val = pthread_mutex_lock(&output_mutex);
    
    if(rt_val != 0)
        error("pthread_mutex_lock");
    
    std::cout << "Thread ID: " << i << " terminating..\n";
    
    rt_val = pthread_mutex_unlock(&output_mutex);
    
    if(rt_val != 0)
        error("pthread_mutex_unlock");
    
    rt_val = pthread_mutex_lock(&mut);
    if(rt_val != 0)
        error("pthread_mutex_lock");
    
    ++num_j;
    
    threads->State(i) = TERM;
    
    rt_val = pthread_mutex_unlock(&mut);
    
    if(rt_val != 0)
        error("pthread_mutex_unlock");
    
    rt_val = pthread_cond_signal(&cond);
    
    if(rt_val != 0)
        error("pthread_mutex_cond");
    
    return 0;
    
}

int main(int argc, char **argv) {
    
    
    if(argc != 2) {
        std::cerr << "Error requires one argument, how many threads..\n" << argv[0] << " numthreads\n";
        exit(EXIT_FAILURE);
    }
    
    int num = atoi(argv[1]);
    if(num <= 0) {
        std::cerr << "Error argument: " << num << "\n";
        exit(EXIT_FAILURE);
    }
    
    total_threads = num;
    threads.reset(new ThreadInfo(num));
    num_t = total_threads;
    num_j = 0;
    
    int rt_val = 0;
    
    for(unsigned int i = 0; i < total_threads; ++i) {
        pthread_t id;
        int sleeptime;
        STATE state;
        timeval t;
        gettimeofday(&t, 0);
        srand(time(0)*t.tv_sec*t.tv_usec);
        sleeptime = rand()%5;
        unsigned long index = i;
        rt_val = pthread_create(&id, 0, thread_func, (void*)index);
        if(rt_val != 0)
            error("pthread_create");
        
        threads->setInfo(i, state, id, sleeptime);
    }
    
    while(num_t > 0) {
        rt_val = pthread_mutex_lock(&mut);
        if(rt_val != 0)
            error("pthread_mutex_lock");
        
        while(num_j == 0) {
            rt_val = pthread_cond_wait(&cond, &mut);
            if(rt_val != 0)
                error("pthread_cond_wait");
        }
        
        for(unsigned int i = 0; i < total_threads; ++i) {
            if(threads->State(i) == TERM) {
                rt_val = pthread_join(threads->getId(i), 0);
                if(rt_val != 0)
                    error("pthread_join");
                threads->State(i) = JOINED;
                --num_j;
                --num_t;
                
                rt_val = pthread_mutex_lock(&output_mutex);
                
                if(rt_val != 0)
                    error("pthread_mutex_lock");
                
                std::cout << "Claimed thread: " << i << " num alive: "<< num_t << "\n";
                
                rt_val = pthread_mutex_unlock(&output_mutex);
                
                if(rt_val != 0)
                    error("pthread_mutex_unlock");
                
            }
        }
        
        rt_val = pthread_mutex_unlock(&mut);
        if(rt_val != 0)
            error("pthread_mutex_unlock");
    }
    
    return EXIT_SUCCESS;
}

void error(const std::string &s) {
    std::cerr << "Error: " << s << "\n";
    exit(EXIT_FAILURE);
}
