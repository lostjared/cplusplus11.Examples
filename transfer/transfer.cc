/*
 
 C++11 example simple tcp/ip networking with sockets.
 
 to send a file:
 
 transfer-tool ipaddress port filename
 
 to serve up files:
 
 transfer-tool port
 
 if your behind a router, be sure to forward that port 
 
 will serve up files in the local directory where the program is ran
 
 written by Jared Bruni
 vist me online @ http://facebook.com/LostSideDead0x
 
  http://lostsidedead.com
 
*/


#include<iostream>
#include<thread>
#include<vector>
#include<fstream>
#include<mutex>
#include"socket.hpp"

// listen_at thread function
void listen_at(std::string user_ip, int sock_id) {
    
    try {
        mx::mxSocket sock{sock_id};
        std::mutex mut;
        int value;
        sock.Read(&value, sizeof(value));
        if(value>0) {
            char *buffer = new char[value+1];
            sock.Read(buffer, value);
            buffer[value] = 0;
            mut.lock();
            std::cout << buffer << "\n";
            std::string file_path=buffer;
            delete [] buffer;
            mut.unlock();
            if(file_path.find("\\") != std::string::npos) {
                mut.lock();
                std::cout << "User: " << user_ip << " Sent illegal filename..\n";
                mut.unlock();
            }
            auto pos = file_path.rfind("/");
            std::string filename=file_path.substr(pos+1,file_path.length()-pos);
            mut.lock();
            std::cout << "Sending... " << filename << "\n";
            mut.unlock();
            std::string src_file="./"+filename;
            std::fstream fs;
            fs.open(src_file, std::ios::in | std::ios::binary);
            if(!fs.is_open()) {
                mut.lock();
                std::cout << "Asked for file not in directory.\n";
                mut.unlock();
                sock.closeSocket();
                return;
            }
            fs.seekg(0, std::ios::end);
            int len = fs.tellg();
            fs.seekg(0, std::ios::beg);
            mut.unlock();
            sock.Write(&len, sizeof(len));
            while(!fs.eof()) {
                char buff[256];
                fs.read(buff, 256);
                int bytes_read=fs.gcount();
                if(bytes_read<=0) break;
                sock.Write(buff, bytes_read);
            }
            sock.closeSocket();
            mut.lock();
            std::cout << " File sent..\n";
            mut.unlock();
            return;
        }
    }
    catch(mx::ReadWriteError) {
        std::cerr << "Error on read/write.\n";
    }
}

// read file to this program on ip, port and filename
void read_file(std::string ip, int port, std::string file_path) {
    mx::mxSocket sock;
    sock.createSocket();
    if(sock.connectTo(ip, port)) {
        int value=file_path.length();
        sock.Write(&value, sizeof(value));
        sock.Write(const_cast<char*>(file_path.c_str()), value);
        std::fstream fs;
        auto p=file_path.rfind("/");
        std::string local_name="downloaded."+file_path.substr(p+1, file_path.length());
        fs.open(local_name, std::ios::binary | std::ios::out);
        int file_size=0;
        sock.Read(&file_size, sizeof(file_size));
        ssize_t rd_bytes=0;
        int packet_size = 255;
        char buffer[255];
        unsigned long total=0;
        while((rd_bytes = sock.Read((char*)buffer,packet_size)) != 0) {
            fs.write(buffer, rd_bytes);
            total += rd_bytes;
            if(total > (unsigned long)file_size) break;
        }
        fs.close();
        sock.closeSocket();
    }
}

int main(int argc, char **argv) {
    try {
        std::vector<std::thread> thread_array;
        if(argc == 2) {
            unsigned int port = atoi(argv[1]);
            bool active = true;
            mx::mxSocket sock;
            sock.createSocket();
            while(active == true) {
                if(sock.listenAt(port)) {
                    std::string user_ip;
                    int sockid = sock.acceptNewSocket(user_ip);
                    std::cout << "Connected to: " << user_ip << "\n";
                    thread_array.emplace_back(listen_at, user_ip, sockid);
                }
            }
        } else if(argc == 4) {
            try {
                std::string ip = argv[1];
                unsigned int port = atoi(argv[2]);
                std::string file_path=argv[3];
                read_file(ip, port, file_path);
            }
            catch(mx::ReadWriteError) {
                std::cerr << "Error on read or write.\n";
            }
        }
    }
    catch(std::exception &e) {
        std::cerr << e.what() << "\n";
    }
    catch(...) {
        std::cerr << "Unkwown Error ..\n";
    }
    return 0;
}
