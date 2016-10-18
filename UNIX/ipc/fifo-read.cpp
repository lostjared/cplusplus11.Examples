/* Adapted from "the Linux Programming Interface"
 Chapter 44
 */
#include "fifo.hpp"
#include<errno.h>
#include<cstring>
#include<string>
#include<iostream>
#include<sstream>


void error(const std::string &func, const std::string &text);

int main(int argc, char **argv) {
    
    int _fd, dum_fd, cli_fd;
    Request req;
    Response resp;
    
    int sq = 0;
    umask(0);
    if(mkfifo(SERVER_NAME, S_IRUSR | S_IWUSR | S_IWGRP) == -1 && errno != EEXIST)
        error("mkfifo", strerror(errno));
    
    _fd = open(SERVER_NAME, O_RDONLY);
    if(_fd == -1)
        error("open", strerror(errno));
    
    dum_fd = open(SERVER_NAME, O_WRONLY);
    if(dum_fd == -1)
        error("open", strerror(errno));
    
    // ignore broken pipe
    if(signal(SIGPIPE, SIG_IGN) == SIG_ERR)
        error("signal", strerror(errno));
    
    while(1) {
        if(read(_fd, &req, sizeof(Request)) != sizeof(Request)) {
            std::cerr << "Error discarding reuqest..\n";
            continue;
        }
        std::ostringstream stream;
        stream << FIFO_NAME_TEMPLATE << (long)req.id;
        cli_fd = open(stream.str().c_str(), O_WRONLY);
        if(cli_fd == -1) {
            std::cerr << "Could not open: " << stream.str() << "\n";
            continue;
        }
        
        resp.len = sq;
        if(write(cli_fd, &resp, sizeof(Response)) != sizeof(Response))
            std::cerr << "Error writing to FIFO\n";
        
        
        if(close(cli_fd) == -1)
            std::cerr << "Error closing..\n";
        
        sq += req.len;
    }
    
    return EXIT_SUCCESS;
}

void error(const std::string &func, const std::string &text) {
    std::cerr << "Error with: " << func << "\nProblem: " << text << "\n";
    exit(EXIT_FAILURE);
}

