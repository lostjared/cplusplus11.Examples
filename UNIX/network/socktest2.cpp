#include<iostream>
#include<string>
#include<sstream>
#include"socket.hpp"


int main(int argc, char **argv) {
    if(argc != 3) {
        std::cerr << "Requires one argument.\n" << argv[0] << " hostname\n";
        exit(EXIT_FAILURE);
    }
    net::ignorePipeSignal();
    net::Socket sock;
    if(sock.connectToHost(argv[1], argv[2], net::SocketType::STREAM) == -1) {
        std::cerr << "Could not connect to host.\n";
        exit(EXIT_FAILURE);
    }
    std::string text;
    std::cout << "Enter String: ";
    std::getline(std::cin, text);
    sock.sendString(text);
    sleep(1);
    char buf[256];
    int bytes = sock.receive(buf, 255);
    buf[bytes] = 0;
    std::cout << "Returned: " << bytes << " buf: " << buf << "\n";
    std::cout << "Quitting..\n";
    sock.closeSocket();
    return 0;
}
