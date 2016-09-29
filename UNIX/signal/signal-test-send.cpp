#include<signal.h>
#include<unistd.h>
#include<iostream>
#include<string>
#include<cstring>
#include<sys/types.h>
#include<sys/wait.h>

void writeOutput(const char *src) {
    write(1, src, strlen(src)); // printf is not reentrant and not safe
    // for use with a signal, so we use write that is async signal safe
}


void handler(int s) {
    writeOutput(" Signal SIGINT caught exiting process\n");
    exit(0);
}

int main(int argc, char **argv) {
    pid_t id = fork();
    if(id == 0) {
    
        if(signal(SIGINT, handler) == SIG_ERR) {
            std::cerr << "Error creating signal..\n";
            exit(EXIT_FAILURE);
        }
        
        int index = 0;
        
        while(1) {
            ++index;
            sleep(3);
            std::cout << "index: " << index << "\n";
        }
    }
    else if(id == -1) {
        std::cerr << "Error on fork..\n";
        exit(EXIT_FAILURE);
    }
    else {
    
        sleep(2);
        std::cout << "Sending SIGINT to pid: " << id << "\n";
        kill(id, SIGINT);
        int status = 0;
        waitpid(id, &status, 0);
        std::cout << "Success..\n";
    }
    return 0;
}

