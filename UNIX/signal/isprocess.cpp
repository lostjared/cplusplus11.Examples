#include<signal.h>
#include<unistd.h>
#include<iostream>
#include<cstring>
#include<errno.h>
#include<cstdlib>


int main(int argc, char **argv) {
    
    if(argc != 3) {
        std::cerr << argv[0] << " processid signum\n";
        exit(EXIT_FAILURE);
    }
    
    long pid = atol(argv[1]);
    long signum = atol(argv[2]);
    
    if(pid <= 0) {
        std::cerr << "Invalid process id..\n";
        exit(EXIT_FAILURE);
    }
    
    int s;
    s = kill(pid, signum);
    if(s == 0) {
        std::cout << "Process exisits..\n";
    } else {
        if(errno == EPERM)
            std::cout << "Process exisits but we don't have permission.\n";
        else if(errno == ESRCH)
            std::cout << "Process does not exisit..\n";
        else {
            std::cout << "Kill.\n";
            exit(EXIT_FAILURE);
        }
    }
    
    return EXIT_SUCCESS;
}
