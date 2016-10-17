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
std::string client_fifo;

void rm_fifo() {
    if(client_fifo.length() > 0)
    	unlink(client_fifo.c_str());
}


int main(int argc, char **argv) {
    
    int _fd, cli_fd;
    Request req;
    Response resp;
    
    umask(0);
    std::ostringstream stream;
    stream << FIFO_NAME_TEMPLATE << (long)getpid();
    client_fifo = stream.str();
    if(mkfifo(client_fifo.c_str(), S_IRUSR | S_IWUSR | S_IWGRP) == -1 && errno != EEXIST)
        error("mkfifo", strerror(errno));
    
    if(atexit(rm_fifo) != 0)
        error("atexit", strerror(errno));;
    
    req.id = getpid();
    req.len = (argc > 1) ? atoi(argv[1]) : 1;
    
    _fd = open(SERVER_NAME, O_WRONLY);
    if(_fd == -1)
        error("open", strerror(errno));
    
    if(write(_fd, &req, sizeof(Request)) != sizeof(Request))
        error("write", "Could not write data");
    
    cli_fd = open(client_fifo.c_str(), O_RDONLY);
    if(cli_fd == -1)
        error("open", strerror(errno));
    
    if(read(cli_fd, &resp, sizeof(Response)) != sizeof(Response))
        error("read", "Error on read ..");
    std::cout << "FIFO Returned: " << resp.len << "\n";
    
    return EXIT_SUCCESS;
}

void error(const std::string &func, const std::string &text) {
    std::cerr << "Error with: " << func << "\nProblem: " << text << "\n";
    exit(EXIT_FAILURE);
}
