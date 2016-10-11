#include<iostream>
#include<unistd.h>
#include<errno.h>
#include<cstring>
#include<sys/wait.h>
#include<signal.h>

void error(const std::string &text);

int main() {
    int fds[2];
    
    if(pipe(fds) == -1)
        error("pipe");
    
    signal(SIGPIPE, SIG_IGN);
    
    pid_t id;
    char buf[1024] = {0};

    switch ((id = fork())) {
        case -1:
            error("Error on fork");
            break;
        case 0:
            close(fds[0]);
            std::cout << "Enter text: ";
            std::cin >> buf;
            write(fds[1], buf, strlen(buf));
            close(fds[1]);
            _exit(EXIT_SUCCESS);
            break;
        default:
            close(fds[1]);
            ssize_t readBytes = read(fds[0], buf, 1024);
            if(readBytes > 0)
                std::cout << "Child returned: " << buf << "\n";
            close(fds[0]);
            break;
    }
    
    waitpid(id, 0, 0);
    
    return EXIT_SUCCESS;
}

void error(const std::string &text) {
    std::cerr << "Error: " << text << " " << strerror(errno) << "\n";
}
