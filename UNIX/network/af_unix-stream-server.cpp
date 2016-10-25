/* Adapted from "the Linux Programming Interface"
 Chapter 57
 */

#include<iostream>
#include<sys/un.h>
#include<sys/socket.h>
#include<string>
#include<cstring>
#include<errno.h>
#include<unistd.h>

const char *SOCK_PATH = "/tmp/testsock";
const int BUF_SIZE=256;

void error(const std::string &text, bool err_no = true);

int main() {
    
    int sockfd;
    sockaddr_un addr;
    int clientfd;
    
    char buf[BUF_SIZE];
    
    sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
    if(sockfd == -1)
        error("socket");

    if(remove(SOCK_PATH) == -1 && errno != ENOENT)
        error("remove");
    
    memset(&addr, 0, sizeof(sockaddr_un));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, SOCK_PATH, sizeof(addr.sun_path)-1);
    
    if(bind(sockfd, (sockaddr *)&addr, sizeof(sockaddr_un)) == -1)
        error("bind");
    
    if(listen(sockfd, 5) == -1)
        error("listen");

    ssize_t bytesRead;
    while(1) {
        clientfd = accept(sockfd, 0, 0);
        if(clientfd == -1)
            error("accept");
        
        while((bytesRead = read(clientfd, buf, BUF_SIZE)) > 0)
            if(write(STDOUT_FILENO, buf, bytesRead) != bytesRead)
                error("partial read/write", false);
        
        if(bytesRead == -1)
            error("read");
        
        if(close(clientfd) == -1)
            error("close");
    }
    return EXIT_SUCCESS;
}

void error(const std::string &text, bool err_no) {
    std::cerr << "Error: " << text << "\n";
    if(err_no) std::cerr << strerror(errno) << "\n";
}
