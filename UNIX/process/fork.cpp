#include<iostream>
#include<cstdio>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

int main() {
    std::cout << "Process started..\n";
    pid_t id = fork();
    switch(id) {
        case -1:
            std::cerr << "Error on fork..\n";
            exit(EXIT_FAILURE);
            break;
        case 0:
            std::cerr << "In Child process..\n";
            // exec here 
            _exit(EXIT_SUCCESS); // use _exit within child process
            break;
        default:
            std::cout << "In Parent..\n";
            
            break;
    }
    int status = 0;
    waitpid(id, &status, 0);
    std::cout << "Program complete..\n";
    exit(EXIT_SUCCESS);
    return EXIT_SUCCESS;
}
