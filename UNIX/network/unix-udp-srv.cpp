/* Adapted from "the Linux Programming Interface"
 Chapter 57
 */
#include<iostream>
#include<sys/socket.h>
#include<sys/un.h>
#include<unistd.h>
#include<cstring>
#include<errno.h>
#include<string>
#include<ctype.h>

static const int BUF_SIZE=10;
static const char *SOCKET_PATH="/tmp/udpsock";

void error(const std::string &text, bool err_no = true);

int main() {
    
    sockaddr_un saddr, caddr;
    int sockfd;
    
    sockfd = socket(AF_UNIX, SOCK_DGRAM, 0);
    if(!sockfd)
        error("socket");
    
    if(remove(SOCKET_PATH) == -1 && errno != ENOENT)
        error("remove");
    
    
    memset(&saddr, 0, sizeof(sockaddr_un));
    saddr.sun_family = AF_UNIX;
    strncpy(saddr.sun_path, SOCKET_PATH, sizeof(saddr.sun_path)-1);
    
    if(bind(sockfd, (sockaddr *)&saddr, sizeof(sockaddr_un)) == -1)
        error("bind");
    
    socklen_t len;
    ssize_t bytesRead;
    char buf[BUF_SIZE];
    
    while(1) {
        len = sizeof(sockaddr_un);
        bytesRead = recvfrom(sockfd, buf, BUF_SIZE,0,(sockaddr *)&caddr, &len);
        if(bytesRead == -1)
            error("recvfrom");
        
        std::cout << "Server received " << bytesRead << " bytes from: " << caddr.sun_path << "\n";
        for(int i = 0; i < bytesRead; ++i)
            buf[i] = toupper((unsigned char)buf[i]);
        
        if(sendto(sockfd, buf, bytesRead, 0, (sockaddr *)&caddr, len) != bytesRead)
            error("fatal error", false);
        
    }
    
    return EXIT_SUCCESS;
}


void error(const std::string &text, bool err_no) {
    std::cerr << "Error: " << text << "\n";
    if(err_no) std::cerr << strerror(errno) << "\n";
}
