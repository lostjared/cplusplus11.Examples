
#include<iostream>
#include"filesend.hpp"
#include<boost/array.hpp>

using boost::asio::ip::tcp;

int main(int argc, char **argv) {
    try {
        if(argc != 3) {
            std::cerr << "Error requires two  arguments: host filename \n";
            return 1;
        }
        boost::asio::io_service io_service;
        tcp::resolver resolver(io_service);
        tcp::resolver::query query(argv[1], "10241");
        tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
        tcp::socket socket(io_service);
        boost::asio::connect(socket, endpoint_iterator);
        if(recvFile(socket, argv[2]) == false) {
            std::cerr << "Failed reading file.\n";
        } else std::cout << "File read.\n";
  
    } catch(std::exception &e) {
        std::cerr << e.what() << "\n";
    }
    return 0;
}
