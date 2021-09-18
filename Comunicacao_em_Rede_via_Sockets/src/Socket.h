#ifndef _SOCKET_H
#define _SOCKET_H

#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <sys/types.h> 
#include <iostream>
// #include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <thread>
#include <vector>

#define PORT 8080
namespace Socket {

   class Server {
      protected:
         int serverFD, last_socket, opt;
         unsigned int _maxClients;
         fd_set readfds; 
         std::vector<int> clientsSockets;
         struct sockaddr_in _address;
         short unsigned int _port;

      // ***Ideias para generalizar o código para qualquer tipo de mensagem ***
         // virtual int readMessage( void *) = 0;
         // virtual void answerMessage(void *msg) = 0;

      public:
         Server(short unsigned int port, unsigned int maxClients);
         ~Server();

         int getServerFD();
         template <typename T>
         void sendMessage(int socket, T* msg, size_t TSize ) {
            send( socket , msg , TSize, 0 );
         }
   };

   class Client {
      protected:
         struct sockaddr_in serv_addr;
         short unsigned int _port;
         int sock = 0; 

      public:
         Client(std::string address, short unsigned port);
         ~Client();

         void connectToServer();
         template <typename T>
         void sendMessage(T* msg, size_t TSize ) {
            send( this->sock, msg , TSize, 0 );
         }

   };
}

#endif