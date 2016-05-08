
// modified example from boost.org

#include <ctime>
#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include<sstream>
using boost::asio::ip::tcp;

std::string randomString() {
    std::ostringstream stream;
    stream << "Hello World Your Random Number is: " << (rand()%255) << "\n";
    return stream.str();
}

int main(int argc, char **argv)
{
    try {
        boost::asio::io_service io_service;
        tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 10241));

        while(1) {
            tcp::socket socket(io_service);
            acceptor.accept(socket);
            std::string message = randomString();
            boost::system::error_code ignored_error;
            boost::asio::write(socket, boost::asio::buffer(message), ignored_error);
        }
    }
    catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
