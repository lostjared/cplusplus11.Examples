//  std::thread Example
//  Created by Jared Bruni on 7/12/13.


#include<iostream>
#include<sstream>
#include<mutex>
#include<cstdlib>
#include<cstdio>
#include<cstring>
#include "socket.hpp"
#include<thread>

std::mutex m_lock;

// Download and Display HTML file from my website
class DownloadFile {
public:
    DownloadFile(std::string url, std::string url_basex) : url_f(url), url_base(url_basex) {}
    void operator()() {
        try {
            mx::mxSocket socket;
            socket.createSocket();
            if(socket.connectTo(mx::getHost(url_base), 80)==false) {
                std::cout << "Error could not connect.\n";
                return;
            }
            std::ostringstream stream;
            stream << "GET /" << url_f << " HTTP/1.0\n\n";
            socket.Write((void*)stream.str().c_str(), stream.str().length());
            
            std::string total;
            
            while(1) {
                static char buf[1024];
                size_t offset = socket.Read(buf, 1023);
                if(offset == 0) break;
                buf[offset] = 0;
                total+=buf;
            }
            
            m_lock.lock();
            std::cout << "File: " << url_f << "\n\n" << total << "\n";
            m_lock.unlock();
            socket.closeSocket();
            
        } catch( ... ) {
            
        }
    }
private:
    std::string url_f, url_base;
};

int main(int argc, char **argv) {
    try {
        DownloadFile dl("index.php", "lostsidedead.com"), dl2("past.php", "lostsidedead.com");
        std::thread down(dl);
        std::thread down2(dl2);
        down.join();
        down2.join();
    } catch (std::exception &e) {
        std::cerr << e.what() << "\n";
    } catch (...) {
        std::cerr << "Unknown error.\n";
    }
    return 0;
}
