#ifndef __FILESEND_H__
#define __FILESEND_H__

#include<boost/asio.hpp>

using boost::asio::ip::tcp;

extern bool sendFile(tcp::socket &socket, std::string filepath);
extern bool recvFile(tcp::socket &socket, std::string filepath);

#endif


