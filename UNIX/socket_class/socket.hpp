#ifndef __SOCKET__H___X
#define __SOCKET__H___X

#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<iostream>
#include<string>
#include<sstream>
#include<unistd.h>
#include<fcntl.h>
#include<cstring>
#include<cstdio>
#include<signal.h>
#include<errno.h>

namespace net {
    
    enum class SocketType { STREAM, DGRAM };
    
    class Socket {
    public:
        Socket();
        Socket(int fd);
        Socket(const Socket &s);
        Socket(Socket &&s);
        Socket &operator=(const Socket &s);
        Socket &operator=(const Socket &&);
        void setSocket(const Socket &s);
        int connectToHost(const std::string &host, const std::string &port, SocketType type);
        int listenAt(const std::string &port, SocketType type, int backlog);
        bool valid() const { return (sockfd >= 0); }
        int &fd() { return sockfd; }
        int acceptSocket(Socket &s);
        ssize_t readLine(std::string &buf);
        std::string readLine(ssize_t &bytesRead);
        ssize_t receive(void *buf, size_t len);
        ssize_t sendData(const void *buf, size_t len);
        ssize_t sendString(const std::string &text);
        int closeSocket();
        void setBlocking(bool state);
    private:
        int sockfd;
        socklen_t addrlen;
        bool blocking;
        
    };
    
    void ignorePipeSignal();
}


















#endif
