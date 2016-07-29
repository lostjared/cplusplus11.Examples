#ifndef __SOCKET__H_
#define __SOCKET__H_

#include<sys/types.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<cstring>
#include<unistd.h>
#include<netdb.h>
typedef int mx_socket;

namespace mx
{

	std::string getHost(std::string text);

    class ReadWriteError {};
    
    /*! \class mxSocket cross platform socket class
      */
     class mxSocket {

     public:
          /*! default constructor creates object */
          mxSocket();
          /*! destructor */
          ~mxSocket();
          /*! creates object with already initalized socket
           * \param nsock socket file descriptor
           */
          mxSocket(mx_socket nsock);
          /*! copy constructor
           * \param nsock init's this object with nsock
           */
          mxSocket(const mxSocket &nsock);
           /*! overloaded operator =
            * \param nsock init's this object with nsock
            * \return this object
            */
          mxSocket &operator=(const mxSocket &nsock);

          /*!
           * createSocket, creates the socket
           * \return true on success
           */
          bool createSocket();

          /*! isConnected
           * \return true if connected
           */
          bool isConnected() { return connected; }
          /*! connectTo connects to ip address and port
           * \param ip ip address
           * \param port outgoing port
           * \return true on success
           */
          bool connectTo(std::string ip, unsigned int port);
          /*!
           * listen for connections at Port
           * \return true if operations successful
           */
          bool listenAt(int port);

          /*! acceptNewSocket accepts new socket when listening
           * \param ip ip of accepted incoming connection
           * \return returns file descriptor of established connection
           */
          mx_socket acceptNewSocket(std::string &ip);
          /*! acceptsocket accepts a incoming connection
           * \return returns file descriptor for incoming connection
           */
          mx_socket acceptsocket();

          /*! Read all reads bytes of size until all have been read
           * \param data pointer to location to hold bytes
           * \param size how many bytes to read
           */
          ssize_t Read(void *data, size_t size);
          /*! Write all reads bytes of size until all have been written
          * \param data pointer to location of bytes
          * \param size how many bytes to write
          */
          ssize_t Write(void *data, size_t size);

          /*! getsocket return current socket file descriptor */
          int getsocket() const { return current_socket; }
          /*! close the socket */
          int closeSocket();
     private:
          mx_socket current_socket;
          bool connected;
     };


      mxSocket::mxSocket()
	  {
		   current_socket = 0;
		   connected = false;
	  }

	  mxSocket::~mxSocket()
	  {

	  }

	  mxSocket::mxSocket(mx_socket nsock)
	  {
		   current_socket = nsock;
		   connected = true;
	  }

	  mxSocket::mxSocket(const mxSocket &nsock)
	  {
		   current_socket = nsock.current_socket;
		   connected = nsock.connected;
	  }

	  mxSocket& mxSocket::operator=(const mxSocket &sock)
	  {

		   current_socket = sock.current_socket;
		   connected = sock.connected;
		   return *this;
	  }

	  bool mxSocket::createSocket()
	  {

		   current_socket = socket(AF_INET,SOCK_STREAM,0);
		   return true;
	  }

	  bool mxSocket::listenAt(int port)
	  {

		   static struct sockaddr_in addy;
		   memset((char*)&addy,0, sizeof(addy));
		   addy.sin_port = htons(port);
		   addy.sin_family = AF_INET;
		   addy.sin_addr.s_addr = INADDR_ANY;
		   int yup = 1;

		   setsockopt(current_socket, SOL_SOCKET,SO_REUSEADDR,(const char*)&yup,sizeof(yup));

		   bind(current_socket, (struct sockaddr *)&addy, sizeof(addy));
           if(listen(current_socket,5) != 0) return false;
		   return true;
	  }


	  mx_socket mxSocket::acceptNewSocket(std::string &ip)
	  {
		   socklen_t caddy_len;
		   static struct sockaddr_in caddy;
		   int s;
		   s = accept(current_socket, (struct sockaddr *)&caddy, &caddy_len);
		   ip = std::string(inet_ntoa(caddy.sin_addr));
		   connected = true;
           return s;
	  }

	  mx_socket mxSocket::acceptsocket()
	  {
		   socklen_t caddy_len;
		   mx_socket SOCK;
		   struct sockaddr_in  caddy;
		   SOCK = accept(current_socket, (struct sockaddr *)&caddy, &caddy_len);
		   connected = true;
           return SOCK;
	  }


	  bool mxSocket::connectTo(std::string where, unsigned int port)
	  {
		   struct sockaddr_in saddy;
		   saddy.sin_port = htons(port);
		   saddy.sin_addr.s_addr = inet_addr(where.c_str());
		   saddy.sin_family = AF_INET;


		   if(connect(current_socket, (const sockaddr*)&saddy, sizeof(sockaddr_in)) == -1) {

				std::cout << "error: could not connect: \n";
                throw ReadWriteError();
				return false;
		   }

		   connected = true;
		   return true;
	  }


	  ssize_t mxSocket::Read(void *data, size_t size)
	  {
		   size_t len = size;
		   size_t total = 0;
		   ssize_t cur_;
		   char *cdata = (char*)data;
		   while ( (len != 0) && ( (cur_ = recv(current_socket, cdata, len, 0) ) != 0) )
		   {
				if(cur_ == -1) {


					 std::cerr << "mxsocket: error on read\n";
                     throw ReadWriteError();
					 return -1;

				}
				len -= cur_;
				cdata += cur_;
				total += cur_;
		   }
		   return total;
	  }

	  ssize_t mxSocket::Write(void *data, size_t size)
	  {
		   size_t len = size;
		   size_t total = 0;
		   ssize_t cur_;
		   char *cdata = (char*)data;
		   while ( (len != 0) && (( cur_ = send(current_socket, cdata, len, 0) ) != 0) )
		   {
				if(cur_ == -1) {
					 std::cerr << "mxsocket: error on write\n";
                    throw ReadWriteError();
					 return -1;

				}
				len -= cur_;
				cdata += cur_;
				total += cur_;
		   }

		   return total;
	  }

	  int mxSocket::closeSocket() {
		   return close(current_socket);
	  }

	  std::string getHost(std::string text) {
		  hostent *record = gethostbyname(text.c_str());
          if(record == 0) {
              return "";
          }
		  in_addr * address = (in_addr * )record->h_addr;
     	  std::string ip_address = inet_ntoa(* address);
		  return ip_address;
	  }


}

#endif

