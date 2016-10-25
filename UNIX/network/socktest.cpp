#include<iostream>
#include<string>
#include<sstream>
#include"socket.hpp"


int main(int argc, char **argv) {
    if(argc != 2) {
        std::cerr << "Requires two arguments.\n" << argv[0] << "hostname\n";
        exit(EXIT_FAILURE);
    }
    net::Socket sock;
    if(sock.connectToHost(argv[1], "80", net::SocketType::STREAM) == -1) {
        std::cerr << "Could not connect to host.\n";
        exit(EXIT_FAILURE);
    }
    std::ostringstream stream;
    stream << "GET /index.html HTTP/1.0\n\n";
    sock.send((void *)stream.str().c_str(), stream.str().length());
    // read rest of data
    while(1) {
        std::string s;
        if(sock.readLine(s) > 0) {
        	std::cout << s << "\n";
        } else break;
    }
    sock.closeSocket();
    return 0;
}
