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

    sockaddr_un addr;
    int sockfd;
    
    sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
    if(sockfd == -1)
        error("socket");
    
    memset(&addr, 0, sizeof(sockaddr_un));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, SOCK_PATH, sizeof(addr.sun_path) -1);
    
    if(connect(sockfd, (sockaddr *)&addr, sizeof(sockaddr_un)) == -1)
        error("connect");
    
    ssize_t bytesRead;
    char buf[BUF_SIZE];
    
    while((bytesRead = read(STDIN_FILENO, buf, BUF_SIZE)) > 0)
        if(write(sockfd, buf, bytesRead) != bytesRead)
            error("partial write", false);
    
    if(bytesRead == -1)
        error("read");
    
    return EXIT_SUCCESS;
}

void error(const std::string &text, bool err_no) {
    std::cerr << "Error: " << text << "\n";
    if(err_no) std::cerr << strerror(errno) << "\n";
}
