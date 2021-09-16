#ifndef _SOCKET_H
#define _SOCKET_H

#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <sys/types.h> 
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <thread>
#include <vector>
#include "Mensagem.h"


#define PORT 8080
namespace Socket {

   class Server {
      protected:
         int serverFD, last_socket, opt, _maxClients;
         fd_set readfds; 
         std::vector<int> clientsSockets;
         struct sockaddr_in _address;
         short unsigned int _port;

      // ***Ideias para generalizar o código para qualquer tipo de mensagem ***
         // Call read with your message pointer and return 0 if a message wasn't read
         // or return any other value otherwise. Ex: return read()
         // virtual int readMessage( void *) = 0;
         // virtual void answerMessage(void *msg) = 0;

      public:
         Server(short unsigned int port, unsigned int maxClients);
         ~Server();

         // virtual std::thread* receberMensagem() = 0;

         // void start();
         int getServerFD();
         template <typename T>
         void sendMessage(int socket, T* msg, size_t TSize ) {
            std::cout << "Message sent" << std::endl;
            send( socket , msg , TSize, 0 );
            // write(socket, msg, TSize);
         }
   };

   class Client {
      protected:
         struct sockaddr_in serv_addr;
         short unsigned int _port;
         // std::string address;
      // char *hello = "Hello from client";
      // Mensagem msg(, 75);

      public:
         int sock = 0; // VOLTAR PRA PROTECTED
         Client(std::string address, short unsigned port);
         ~Client();

         template <typename T>
         void sendMessage(T* msg, size_t TSize ) {

            std::cout << "Message sent" << std::endl;
            send( this->sock, msg , TSize, 0 );
            // write(this->sock, msg, TSize);
         }

   };
}

#endif