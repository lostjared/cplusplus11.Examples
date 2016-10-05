#include<sched.h>
#include<iostream>
#include<string>
#include<errno.h>
#include<cstring>

void error(const std::string &text);
int policytoint(const char &c);

int main(int argc, char **argv) {
    
    int i, policy;
    struct sched_param sp;
    
    if(argc < 3) {
        std::cerr << "Error requires 3 arguments..\n" << argv[0] << " " << "policy priority pid\n";
        exit(EXIT_FAILURE);
    }
    
    policy = policytoint(argv[1][0]);
    sp.sched_priority = atol(argv[2]);
    
    for(i = 3; i < argc; ++i) {
        if(sched_setscheduler(atol(argv[i]), policy, &sp) == -1)
            error("sched_setscheduler");
    }
    
    return EXIT_SUCCESS;
}

void error(const std::string &text) {
    std::cerr << "Error: " << text << " " << strerror(errno) << "\n";
    exit(EXIT_FAILURE);
}

int policytoint(const char &c) {
    switch(c) {
        case 'r': return SCHED_RR;
        case 'f': return SCHED_FIFO;
#ifdef SCHED_BATCH
        case 'b': return SCHED_BATCH;
#endif
#ifdef SCHED_IDLE
        case 'i': return SCHED_IDLE;
#endif
            
    }
    return SCHED_OTHER;
}
