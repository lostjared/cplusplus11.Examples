#include<iostream>
#include<string>
#include<unistd.h>
#include<fcntl.h>
#include<ctime>
#include<poll.h>
#include<errno.h>
#include<cstring>
#include<sys/wait.h>

void error(const std::string &text, bool err_no = true);

int main(int argc, char **argv) {

    pollfd pfd;
    int fds[2];
    
    if(pipe(fds) == -1)
        error("pipe");
    
    pid_t id;
    
    switch((id = fork())) {
        case -1:
            std::cerr << "Error on fork..\n";
            error("fork");
            break;
        case 0: {
            close(fds[0]);
            sleep(3);
            char buf[255];
            snprintf(buf, 254, "Hey this was sent..\n");
            
            int len = strlen(buf);
            
            if(write(fds[1], buf, len) != len)
                std::cerr << "Error: partial write..\n";
            
            _exit(0);
        }
            break;
        default: {
            close(fds[1]);
            pfd.fd = fds[0];
            pfd.events = POLLIN;
            bool active = true;
            while(active) {
                int rt_val = poll(&pfd, 1, 0);
                if(rt_val == -1)
                    error("error on poll");
                
                if(pfd.revents & POLLIN) {
                    ssize_t bytesRead;
                    char buf[255];
                    
                    while((bytesRead = read(fds[0], buf, 255)) > 0)
                        if(write(STDOUT_FILENO, buf, bytesRead) != bytesRead)
                            error("partial write", false);
                    
                    active = false;
                    
                } else {
                    std::cout << "Waiting . . .\n";
                }
                
            }
        }
            break;
    }
    
    waitpid(id, 0, 0);
    
    
    return EXIT_SUCCESS;
}

void error(const std::string &text, bool e) {
    std::cerr << "Error: " << text << "\n";
    if(e) std::cerr << strerror(errno) << "\n";
    exit(EXIT_FAILURE);
}
