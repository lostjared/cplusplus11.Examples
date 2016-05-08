
#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include<sstream>
#include"filesend.hpp"

using boost::asio::ip::tcp;

int main(int argc, char **argv)
{
    try {
        boost::asio::io_service io_service;
        tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 10241));

        while(1) {
            tcp::socket socket(io_service);
            acceptor.accept(socket);
            if(sendFile(socket, argv[1]) == false) {
                std::cerr << "Failed to send file.\n";
            } else std::cout << "Success file sent.\n";
        }
    }
    catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
