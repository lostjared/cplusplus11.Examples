// modified example from boost.org

#include<iostream>
#include<boost/asio.hpp>
#include<boost/array.hpp>

using boost::asio::ip::tcp;

int main(int argc, char **argv) {
    try {
        if(argc != 2) {
            std::cerr << "Error requires one argument.\n";
            return 1;
        }
        boost::asio::io_service io_service;
        tcp::resolver resolver(io_service);
        tcp::resolver::query query(argv[1], "10421");
        tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
        tcp::socket socket(io_service);
        boost::asio::connect(socket, endpoint_iterator);
        while(1) {
            boost::array<char, 128> buf;
            boost::system::error_code error;
            size_t len = socket.read_some(boost::asio::buffer(buf), error);
            if(error == boost::asio::error::eof)
                break;
            else if(error)
                throw boost::system::system_error(error);
            
            std::cout.write(buf.data(), len);
        }
    } catch(std::exception &e) {
        std::cerr << e.what() << "\n";
    }
    return 0;
}