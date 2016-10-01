/*
 Modeled (Converted to C++ and modified) From
 "The Linux Programming Interface"
 Listing 27-9 on page 586-587
*/

#include<iostream>
#include<string>
#include<signal.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<errno.h>

int System(const std::string &command) {
    sigset_t bmask, omask;
    struct sigaction sa_ignore, sa_oquit, sa_origint, sa_default;
    pid_t id;
    int status, serrno;
    
    if(command == "") return System(":") == 0;
    
    sigemptyset(&bmask);
    sigaddset(&bmask, SIGCHLD);
    sigprocmask(SIG_BLOCK, &bmask, &omask);
    sa_ignore.sa_handler = SIG_IGN;
    sa_ignore.sa_flags = 0;
    sigemptyset(&sa_ignore.sa_mask);
    sigaction(SIGINT, &sa_ignore, &sa_origint);
    sigaction(SIGQUIT, &sa_ignore, &sa_oquit);
    
    switch((id = fork())) {
        case -1:
            status = -1;
            break;
        case 0:
            sa_default.sa_handler = SIG_DFL;
            sa_default.sa_flags = 0;
            sigemptyset(&sa_default.sa_mask);
            if(sa_origint.sa_handler != SIG_IGN)
                sigaction(SIGINT, &sa_default, NULL);
            if(sa_oquit.sa_handler != SIG_IGN)
                sigaction(SIGQUIT, &sa_default, NULL);
            
            execl("/bin/sh", "sh", "-c", command.c_str(), (char*)NULL);
            _exit(127);
            break;
        default:
            while(waitpid(id, &status, 0) == -1) {
                if(errno != EINTR) {
                    status = -1;
                    break;
                }
            }
            break;
    }
    serrno = errno;
    sigprocmask(SIG_SETMASK, &omask, NULL);
    sigaction(SIGINT, &sa_origint, NULL);
    sigaction(SIGQUIT, &sa_oquit, NULL);
    errno = serrno;
    return status;
}


int main() {
    while(1) {
        std::cout << "Enter Command: ";
        std::string command;
        std::getline(std::cin, command);
        if(command=="Quit") exit(EXIT_SUCCESS);
        System(command);
    }
    return EXIT_SUCCESS;
}
