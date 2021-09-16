#include "Socket.h"

namespace Socket {

   Server::Server(short unsigned int port, unsigned int maxClients)  
   {

    this->_maxClients = maxClients;
    this->clientsSockets.reserve(this->_maxClients);
      // std::this_thread::sleep_for(1);
      // this->_port = port;
      // this->opt = 1;
      // //  int addrlen = sizeof(this->address);
      // // char buffer[1024] = {0};
      

      // // Creating socket file descriptor
      // if ((this->server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
      // {
      //    perror("socket failed");
      //    exit(EXIT_FAILURE);
      // }

      // // TENTATIVA DE DEIXAR NAO BLOQUEANTE
      // // int flags = fcntl(this->server_fd, F_GETFL);
      // // fcntl(this->server_fd, F_SETFL, flags | O_NONBLOCK);

      // // Forcefully attaching socket to the port
      // if (setsockopt(this->server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
      //                                              &(this->opt), sizeof(this->opt)))
      // {
      //    perror("setsockopt");
      //    exit(EXIT_FAILURE);
      // }
      // this->_address.sin_family = AF_INET;
      // this->_address.sin_addr.s_addr = INADDR_ANY;
      // this->_address.sin_port = htons( port );
         
      // // Forcefully attaching socket to the port
      // if (bind(this->server_fd, (struct sockaddr *)&(this->_address), 
      //                            sizeof(this->_address))<0)
      // {
      //    perror("bind failed");
      //    exit(EXIT_FAILURE);
      // }

   //       if (listen(this->server_fd, 3) < 0) {
   //       perror("listen");
   //       exit(EXIT_FAILURE);
   // }
   // std::cout << "Passou do listen" << std::endl;
   // if ((last_socket = accept(this->server_fd, (struct sockaddr *)&(this->address), 
   //                   (socklen_t*)&addrlen))<0)
   // {
   //    perror("accept");
   //    exit(EXIT_FAILURE);
   // }  

   this->opt = 1;  
   // int addrlen, new_socket, activity, i , valread , sd;  
   //  int max_sd;  
   //  struct sockaddr_in address;  
         
   //  char buffer[1025];  //data buffer of 1K 
         
    //set of socket descriptors 
   //  fd_set readfds;  
         
    //a message 
   //  char *message = "ECHO Daemon v1.0 \r\n";  
     
    //initialise all client_socket[] to 0 so not checked 
    for (int i = 0; i < this->_maxClients; i++)  
    {  
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
    this->_address.sin_port = htons( PORT );  
         
    //bind the socket to localhost port 8888 
    if (bind(this->serverFD, (struct sockaddr *)&this->_address, sizeof(this->_address))<0)  
    {  
        perror("bind failed");  
        exit(EXIT_FAILURE);  
    }  
   //  printf("Listener on port %d \n", PORT);  
         std::cout << "Listener on port " << port << std::endl;
    //try to specify maximum of 3 pending connections for the master socket 
    if (listen(this->serverFD, 3) < 0)  
    {  
        perror("listen");  
        exit(EXIT_FAILURE);  
    }  
         
    //accept the incoming connection 
   //  addrlen = sizeof(address);  
   //  puts("Waiting for connections ...");  
   
      
   }  

   Server::~Server() {}

//    void Server::start() {
//       int sd, max_sd, activity, new_socket;
//       long int valread;
//       int addrlen = sizeof(this->_address);
//     //   char buffer [1025];
//     Mensagem msg;
//       std::string message;      

//       std::cout << "Waiting for connections ..." << std::endl;
//       while(1) {  
//         //clear the socket set 
//         FD_ZERO(&readfds);  
     
//         //add master socket to set 
//         FD_SET(this->serverFD, &readfds);  
//         max_sd = this->serverFD;  
             
//         //add child sockets to set 
//         for (int i = 0 ; i < this->_maxClients ; i++)  
//         {  
//             //socket descriptor 
//             sd = this->clientsSockets[i];  
                 
//             //if valid socket descriptor then add to read list 
//             if(sd > 0)  
//                 FD_SET( sd , &readfds);  
                 
//             //highest file descriptor number, need it for the select function 
//             if(sd > max_sd)  
//                 max_sd = sd;  
//         }  
     
//         //wait for an activity on one of the sockets , timeout is NULL , 
//         //so wait indefinitely 
//         activity = select( max_sd + 1 , &readfds , NULL , NULL , NULL);  
       
//         if ((activity < 0) && (errno!=EINTR))  
//         {  
//             // printf("select error");  
//             std::cout << "select error" << std::endl;
//         }  
             
//         //If something happened on the master socket, then its an incoming connection 
//         if (FD_ISSET(this->serverFD, &readfds))  
//         {  
//             if ((new_socket = accept(this->serverFD, 
//                     (struct sockaddr *)&_address, (socklen_t*)&addrlen))<0)  
//             {  
//                 perror("accept");  
//                 exit(EXIT_FAILURE);  
//             }  
             
//             //inform user of socket number - used in send and receive commands 
//             // printf("New connection , socket fd is %d , ip is : %s , port : %d\n" , new_socket ,
//             //    inet_ntoa(_address.sin_addr) , ntohs(_address.sin_port));  
           
//             //send new connection greeting message 

//             message = "Seja bem-vindo à loja de bebidas!\n";
//             message += "Faça seu pedido digitando o número correspondente à bebida desejada e a quantidade no formato {bebida quantidade}.\n";
//             message += "Menu: \n";
//             message += "1 -> Água\n";
//             message += "2 -> Cerveja\n";
//             message += "3 -> Refrigerante\n";
//             message += "0 -> Sair da loja\n";
//             if( send(new_socket, message.c_str(), message.size(), 0) != (unsigned) message.size() )  
//             {  
//                 perror("send");  
//             }  
                 
//             // puts("Welcome message sent successfully"); 
//             std::cout << "Cliente " << new_socket << " chegou na loja." << std::endl; 
                 
//             //add new socket to array of sockets 
//             for (int i = 0; i < this->_maxClients; i++)  
//             {  
//                 //if position is empty 
//                 if( this->clientsSockets[i] == 0 )  
//                 {  
//                     this->clientsSockets[i] = new_socket;  
//                     printf("Adding to list of sockets as %d\n" , i);  
                         
//                     break;  
//                 }  
//             }  
//         }  
//         //else its some IO operation on some other socket
//         for (int i = 0; i < this->_maxClients; i++)  
//         {  
//             sd = this->clientsSockets[i];  
                 
//             if (FD_ISSET( sd , &(this->readfds)))  
//             {  
//                 //Check if it was for closing , and also read the 
//                 //incoming message 
//                 if ((valread = read( sd, &msg, sizeof(Mensagem))) == 0)  
//                 {  
//                     //Somebody disconnected , get his details and print 
//                     getpeername(sd , (struct sockaddr*)&_address , (socklen_t*)&addrlen);  
//                     printf("Host disconnected , ip %s , port %d \n" , 
//                     inet_ntoa(_address.sin_addr) , ntohs(_address.sin_port));  
                         
//                     //Close the socket and mark as 0 in list for reuse 
//                     close( sd );  
//                     this->clientsSockets[i] = 0;  
//                 }  
                     
//                 //Echo back the message that came in 
//                 else 
//                 {  

//                     message = "Pedido recebido!";

//                     //set the string terminating NULL byte on the end 
//                     //of the data read 
//                     // answerMessage(buffer);
//                     this->sendMessage(sd, message.c_str(), message.size());
//                     // buffer[valread] = '\0';  
//                     // send(sd , buffer , strlen(buffer) , 0 );  
//                 }  
//             }  
//         }  
//     }  
//    }
   int Server::getServerFD() {
      return this->serverFD;
   }

   Client::Client(std::string address, short unsigned port) {
      // char buffer[1024] = {""};

      if ((this->sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
      {
        printf("\n Socket creation error \n");
        exit(EXIT_FAILURE);
      }
   
   this->serv_addr.sin_family = AF_INET;
   this->serv_addr.sin_port = htons(port);
       
    // Convert IPv4 and IPv6 addresses from text to binary form
   if(inet_pton(AF_INET, address.c_str(), &serv_addr.sin_addr)<=0) 
   {
      printf("\nInvalid address/ Address not supported \n");
      exit(EXIT_FAILURE);
   }

               if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
            {
               printf("\nConnection Failed \n");

               exit(EXIT_FAILURE);
            }
   std::cout << "Connecting to " << address << " at port " << port << std::endl;
   // "127.0.0.1"


   // std::cout << msg.getQuantidade() << std::endl;
   // send(sock , &msg, sizeof(Mensagem) , 0 );
   // printf("Hello message sent\n");
   // valread = read( sock , buffer, 1024);
   // printf("%s\n",buffer );
   // return 0;
   }

   Client::~Client() {}
}