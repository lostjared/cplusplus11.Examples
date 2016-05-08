#include<iostream>
#include<sstream>
#include<boost/asio.hpp>
#include<boost/array.hpp>
#include<fstream>

using boost::asio::ip::tcp;

int main(int argc, char **argv) {
    try {
        if(argc != 4) {
            std::cerr << "Error requires three arguments.\n" << argv[0] << " domain filepath output-filename\n";
            // try running program with arguments
            // ./download-test lostsidedead.com index.php output.php
            return 1;
        }
        boost::asio::io_service io_service;
        tcp::resolver resolver(io_service);
        tcp::resolver::query query(argv[1], "80");
        tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
        tcp::socket socket(io_service);
        boost::asio::connect(socket, endpoint_iterator);
        std::ostringstream stream;
        stream << "GET /" << argv[2] << " HTTP/1.0\n\n";
        std::string message = stream.str();
        boost::system::error_code ie;
        boost::asio::write(socket, boost::asio::buffer(message), ie);
        std::fstream file;
        file.open(argv[3], std::ios::out | std::ios::binary);
        if(!file.is_open()) {
            std::cerr << "Could not open output file.\n";
            return 1;
        }
        while(1) {
            boost::array<char, 128> buf;
            boost::system::error_code error;
            size_t len = socket.read_some(boost::asio::buffer(buf), error);
            if(error == boost::asio::error::eof)
                break;
            else if(error)
                throw boost::system::system_error(error);
            
            file.write(buf.data(), len);
        }
        file.close();
        std::cout << "Downloaded file to: " << argv[3] << "\n";
    } catch(std::exception &e) {
        std::cerr << e.what() << "\n";
    }
    return 0;
}