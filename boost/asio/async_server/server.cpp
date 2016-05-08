
#include<iostream>
#include<sstream>
#include<boost/asio.hpp>
#include<boost/bind.hpp>
#include<boost/shared_ptr.hpp>
#include<boost/enable_shared_from_this.hpp>
using boost::asio::ip::tcp;

std::string make_random_string() {
    std::ostringstream stream;
    stream << "Random number is: " << rand()%0xFFFFFFFF << "\n";
    return stream.str();
}

class exConnection : public boost::enable_shared_from_this<exConnection> {
public:
    
    
    typedef boost::shared_ptr<exConnection> pointer;
    
    static pointer create(boost::asio::io_service &io_service) {
        return pointer(new exConnection(io_service));
    }
    
    tcp::socket &socket() {
        return socket_;
    }
    
    void start() {
        message_ = make_random_string();
        boost::asio::async_write(socket_, boost::asio::buffer(message_), boost::bind(&exConnection::handle_write, shared_from_this(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
        
    }

private:
    void handle_write(const boost::system::error_code &error, size_t bytes_transferred) {
        
        std::cout << "write complete sent: " << bytes_transferred << " bytes.\n";
    }
  
    exConnection(boost::asio::io_service &service) : socket_(service) {
        
    }
    
    tcp::socket socket_;
    std::string message_;
    

};

class exServer {
public:
    exServer(boost::asio::io_service &io_service, int port) : acceptor_(io_service, tcp::endpoint(tcp::v4(), port)) {
        start_accept();
    }
            
    void start_accept() {
        exConnection::pointer new_con = exConnection::create(acceptor_.get_io_service());
        acceptor_.async_accept(new_con->socket(), boost::bind(&exServer::handle_accept, this, new_con, boost::asio::placeholders::error));
    }
    
    void handle_accept(exConnection::pointer new_con, const boost::system::error_code &e) {
        if(!e) {
            new_con->start();
        }
        start_accept();
    }
    
    tcp::acceptor acceptor_;
    
};


int main(int argc, char **argv) {
    try {
    
        boost::asio::io_service io_service;
        exServer serv(io_service, 10421);
        io_service.run();
    
    } catch(std::exception &e) {
        std::cerr << e.what() << "\n";
    }
    return 0;
}
