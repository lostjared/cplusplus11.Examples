/* 

 boost::asio Test Program
 Responds to simple HTTP GET command
 Tested with Google Chrome

 written by Jared Bruni
 
 http://objective-c.info
 
*/

#include<iostream>
#include<string>
#include"boost/asio.hpp"
#include"boost/array.hpp"
#include<thread>
#include<mutex>
#include<vector>
#include<sstream>
#include<fstream>

using boost::asio::ip::tcp;

void procFile(tcp::socket *socket);
std::string total_path;

int main(int argc, char **argv) {
    if(argc != 3) {
        std::cerr << "Requires port/directory.\n " << argv[0] << " port path\n";
        return 1;
    }
    total_path = argv[2];
    boost::asio::io_service io_service;
    tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), atoi(argv[1])));
    while(1) {
        tcp::socket *socket = new tcp::socket(io_service);
        acceptor.accept(*socket);
        std::thread ts(procFile, socket);
        ts.detach();
    }
    return 0;
}

void tokenize_string(std::string textval, std::vector<std::string> &text_arr) {
    std::istringstream istream(textval);
    std::string text;
    while(istream >> text) {
        text_arr.push_back(text);
    }
}

int find_in(std::vector<std::string> &v, std::string text) {
    for(unsigned int i = 0; i < v.size(); ++i) if(v[i] == text) return i;
    return -1;
}

void sendError(tcp::socket *socket, std::string text) {
    std::ostringstream stream;
    stream << text << " \n\n";
    boost::system::error_code ie;
    boost::asio::write(*socket, boost::asio::buffer(stream.str()), ie);
}

void procFile(tcp::socket *socket) {
    try {
        boost::system::error_code ie;
        std::ostringstream stream;
        char buffer[5000];
        memset(buffer, 0, sizeof(buffer));
        size_t len = socket->read_some(boost::asio::buffer(buffer, 5000), ie);
        stream.write(buffer, len);
        std::vector<std::string> words;
        tokenize_string(stream.str(), words);
        int findGet = find_in(words, "GET");
        if(findGet == -1 || findGet+1 > words.size()) {
            std::cerr << "Error command does not contain proper get command.\n";
            delete socket;
            return;
        }
        std::string filePath = words[findGet+1];
        if(filePath[0] == '/') {
            if(filePath.find("..") != -1) {
                std::cerr << "Error does not support path component ..\n";
                sendError(socket, "fileserv: Does not support path component..\n");
                delete socket;
                return;
            }
            std::ostringstream ss;
            ss << total_path << filePath;
            std::cout << "File to send: " << ss.str() << "\n";

            std::fstream file;
            file.open(ss.str(), std::ios::in | std::ios::binary);
            if(!file.is_open()) {
                std::cerr << "File not found..\n";
                sendError(socket, "HTTP/1.1 404 Not Found\nAccept-Ranges: bytes\nConnection: close\nContent-Type: text/html\n\n fileserv: 404 File Not Found!");
                delete socket;
                return;
            }
            while(!file.eof()) {
                char buff[1024];
                memset(buff, 0, sizeof(buff));
                file.read(buff, 1024);
                int bytesRead = file.gcount();
                boost::asio::write(*socket, boost::asio::buffer(buff, bytesRead), ie);
                
            }
            file.close();
        }
    }
    catch(std::exception &e) {
        std::cerr << e.what() << "\n";
    }
 
    delete socket;
}

