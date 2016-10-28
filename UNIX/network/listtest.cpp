#include<iostream>
#include<string>
#include "socket.hpp"
#include<poll.h>
#include<vector>
#include<thread>
#include<deque>

std::vector<net::Socket> svec;
std::deque<std::string> messages;
std::mutex mut;

void readAll();
void repeatAll();

int main(int argc, char **argv) {
    net::ignorePipeSignal();
    net::Socket s;
    if(s.listenAt("5002", net::SocketType::STREAM, 5) == -1) {
        std::cerr << "Error listening..\n";
        exit(EXIT_FAILURE);
    }
    std::thread ra(readAll);
    std::cout << "Entering loop for accept on "<< s.fd() << "..\n";
    while(1) {
        net::Socket sp;
        sp = s.acceptSocket();
        int flags = fcntl(sp.fd(), F_GETFL);
        flags |= O_NONBLOCK;
        fcntl(sp.fd(), F_SETFL, flags);
        std::cout << "Accepted connection\n";
        mut.lock();
        svec.push_back(sp);
        mut.unlock();
    }
    
    s.closeSocket();
    ra.join();
    return 0;
}

void readAll() {
    pollfd pfd;
	while(1) {
        mut.lock();
        if(svec.size() == 0) {
            mut.unlock();
            continue;
        }
         for(auto sock = svec.begin(); sock != svec.end(); ++sock) {
            pfd.fd = sock->fd();
            pfd.events = POLLIN;
            
            if(poll(&pfd, 1, 0) == -1) {
                continue;
            }
            
            if(pfd.revents & POLLIN) {
                char buf[0xFF];
                ssize_t bytesRead;
                std::string text="";
                while((bytesRead = read(sock->fd(), buf, 0xFF)) > 0) {
                    text += buf;
                }
                if(text.length() > 0) {
                	messages.push_back(text);
                    std::cout << "Added Message: " << text << "\n";
                }
               
            } else continue;
        }
        if(messages.size() > 0) {
            for(int i = 0; i < svec.size(); ++i) {
                int rt_val;
                std::cout << "Writing to: " << svec[i].fd() << " with: " << messages[0].c_str()<< "\n";
                rt_val = write(svec[i].fd(), messages[0].c_str(), messages[0].length());
                if(rt_val == EPIPE || rt_val == -1) {
                    svec.erase(svec.begin()+i);
                    std::cout << "Broken pipe: " << svec[i].fd() << "\n";
                    continue;
                } else if(rt_val == EAGAIN)
                    continue;
            }
            messages.pop_front();
        }
        mut.unlock();
    }
}

