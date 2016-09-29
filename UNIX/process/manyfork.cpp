#include<iostream>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<sys/time.h>
#include<cstdlib>
#include<errno.h>
#include<ctime>

int main(int argc, char **argv) {
    pid_t id;
    for(int i = 0; i < 4; ++i) {
        id = fork();
        switch(id) {
            case -1:
                std::cerr << "Error on fork()\n";
                exit(EXIT_FAILURE);
                break;
            case 0: {
                timeval t;
                gettimeofday(&t, 0);
                srand(t.tv_sec * t.tv_usec);
                std::cout << "In child process waiting....\n";
                sleep(rand()%10);
                std::cout << getpid() << " is exiting..\n";
                _exit(EXIT_SUCCESS);
            }
                break;
            default:
                break;
        }
    }
    pid_t cid;
    
    while((cid = wait(0)) != -1)
        continue;
    
    if(errno != ECHILD)
        std::cerr << "Error waiting..\n";
    
    std::cout << "Complete.\n";
    return EXIT_SUCCESS;
}
