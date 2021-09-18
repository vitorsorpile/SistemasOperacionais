#include "Socket.h"

namespace Socket {

   Server::Server(short unsigned int port, unsigned int maxClients) {
      this->_port = port;
      this->_maxClients = maxClients;
      this->clientsSockets.reserve(this->_maxClients);

      this->opt = 1;  

      //initialise all clientsSockets to 0 so not checked 
      for (unsigned int i = 0; i < this->_maxClients; i++) {  
         this->clientsSockets[i] = 0;  
      }  
      
      //create a master socket 
      if( (this->serverFD = socket(AF_INET , SOCK_STREAM , 0)) == 0)  
      {  
         perror("socket failed");  
         exit(EXIT_FAILURE);  
      }  
     
      //set master socket to allow multiple connections , 
      //this is just a good habit, it will work without this 
      if( setsockopt(this->serverFD, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, 
            sizeof(opt)) < 0 )  
      {  
         perror("setsockopt");  
         exit(EXIT_FAILURE);  
      }  
      
      //type of socket created 
      this->_address.sin_family = AF_INET;  
      this->_address.sin_addr.s_addr = INADDR_ANY;  
      this->_address.sin_port = htons( port );  
            
      //bind the socket to localhost port 
      if (bind(this->serverFD, (struct sockaddr *)&this->_address, sizeof(this->_address))<0)  
      {  
         perror("bind failed");  
         exit(EXIT_FAILURE);  
      }  

      //try to specify maximum of 3 pending connections for the master socket 
      if (listen(this->serverFD, 3) < 0)  
      {  
         perror("listen");  
         exit(EXIT_FAILURE);  
      }  
   }  

   Server::~Server() {}

   int Server::getServerFD() {
      return this->serverFD;
   }


   Client::Client(std::string address, short unsigned port) {
      this->_port = port;

      if ((this->sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
      {
        std::cout << "Socket creation error" << std::endl;
        exit(EXIT_FAILURE);
      }
      this->serv_addr.sin_family = AF_INET;
      this->serv_addr.sin_port = htons(port);
         
      // Convert IPv4 and IPv6 addresses from text to binary form
      if(inet_pton(AF_INET, address.c_str(), &serv_addr.sin_addr)<=0) 
      {
         std::cout << "Invalid address/ Address not supported" << std::endl;
         exit(EXIT_FAILURE);
      }   
   }

   void Client::connectToServer() {
      if (connect(this->sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
      {
         std::cout << "Connection Failed" << std::endl;
         exit(EXIT_FAILURE);
      }   
   }

   Client::~Client() {}
}