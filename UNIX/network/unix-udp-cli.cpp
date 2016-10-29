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

static const int BUF_SIZE=10;
static const char *SOCKET_PATH="/tmp/udpsock";
void error(const std::string &text, bool err_no = true);

int main(int argc, char **argv) {
    
    sockaddr_un saddr, caddr;
    int sockfd;
    
    sockfd = socket(AF_UNIX, SOCK_DGRAM, 0);
    if(!sockfd)
        error("socket");
    
    memset(&caddr, 0, sizeof(sockaddr_un));
    caddr.sun_family = AF_UNIX;
    snprintf(caddr.sun_path, sizeof(caddr.sun_path), "/tmp/udpsock%ld", (long)getpid());
    if(bind(sockfd, (sockaddr *)&caddr, sizeof(sockaddr_un)) == -1)
        error("bind");
    
    memset(&saddr, 0, sizeof(sockaddr_un));
    saddr.sun_family = AF_UNIX;
    strncpy(saddr.sun_path, SOCKET_PATH, sizeof(saddr.sun_path)-1);
    char resp[BUF_SIZE];
    
    for(int i = 1; i < argc; ++i) {
        ssize_t msg_len;
        ssize_t bytesRead;
        msg_len = strlen(argv[i]);
        if(sendto(sockfd, argv[i], msg_len, 0, (sockaddr *)&saddr, sizeof(sockaddr_un)) != msg_len)
            error("send to error", false);
     
        bytesRead = recvfrom(sockfd, resp, BUF_SIZE, 0, NULL, NULL);
        if(bytesRead == -1)
            error("recvfrom");
        
        resp[bytesRead] = '\0';
        std::cout << "Response: " << bytesRead <<  " bytes, response: " << resp << "\n";
    }
    
    remove(caddr.sun_path);
    return EXIT_SUCCESS;
}


void error(const std::string &text, bool err_no) {
    std::cerr << "Error: " << text << "\n";
    if(err_no) std::cerr << strerror(errno) << "\n";
}
