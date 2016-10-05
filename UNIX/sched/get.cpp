#include<sched.h>
#include<iostream>
#include<string>
#include<errno.h>
#include<cstring>


void error(const std::string &text);
std::string getpolicystr(int p);

int main(int argc, char **argv) {
    int i, policy;
    sched_param sp;
    for(i = 1; i < argc; ++i) {
        long p = atol(argv[i]);
        policy = sched_getscheduler(p);
        if(policy == -1)
            error("sched_getscheduler");
        if(sched_getparam(policy ,&sp) == -1)
            error("sched_getparam");
        
        std::cout << argv[i] << ": " << getpolicystr(policy) << " " << policy <<  " " << sp.sched_priority << "\n";
    }
    
    return EXIT_SUCCESS;
}

void error(const std::string &text) {
    std::cerr << "Error: " << text << " " << strerror(errno) << "\n";
    exit(EXIT_FAILURE);
}

std::string getpolicystr(int p) {
    switch(p) {
        case SCHED_OTHER: return "OTHER";
        case SCHED_RR: return "RR";
        case SCHED_FIFO: return "FIFO";
#ifdef SCHED_BATCH
        case SCHED_BATCH: return "BATCH";
#endif
#ifdef SCHED_IDLE
        case SCHED_IDLE: return "IDLE";
#endif
    }
    return "??";
}
