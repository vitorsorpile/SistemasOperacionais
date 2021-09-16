#include "Loja.h"

// void  Loja::atenderCliente(Loja* loja, int cliente) {
     
//      std::cout << "Entrou na test " << cliente << std::endl;
     
//    while (1) {
//       loja->imprimeEstoque();

//       if (loja->estoqueVazio()) close(loja->getServerFD());
//    Mensagem msg;
//    char buffer[1024] = {0};
//    read( cliente , &msg, sizeof(Mensagem) );
//    // read( cliente , buffer, 1024 );
//    // std::cout << "test buffer: " << buffer << std::endl;
//    // std::cout << msg.getQuantidade() << std::endl;
//    // std::string str = "Pedido recebido";
//    std::string str;

//    // send( cliente , str.c_str() , str.size(), 0 );

//    // continue;
//    // return;
//    switch (msg.getTipo())
//    {

//    case tipoDaMensagem::ENTRADA :
//       std::cout << "Cliente " << cliente << " chegou na loja." << std::endl;
//       str = "Seja bem-vindo à loja de bebidas!\n";
//       str += "Faça seu pedido digitando o número correspondente à bebida desejada e a quantidade separadas por espaço.\n";
//       str += "Menu: \n";
//       str += "1 -> Água\n";
//       str += "2 -> Cerveja\n";
//       str += "3 -> Refrigerante\n";
//       str += "0 -> Sair da loja\n";
//       break;
   
//    case tipoDaMensagem::PEDIDO:
//       if (loja->tratarPedido(msg.getBebida(), msg.getQuantidade())) {
//          str = "Aqui está seu pedido.\n";
//       }
//       else {
//          str = "Seu pedido não pode ser atendido.\n";
//       }
//       break;

//    case tipoDaMensagem::SAIDA:
//       str = "Muito obrigado! Volte sempre!\n";
//       break;
//    default:
//       str = "Mensagem inválida\n";
//       break;
//    }
//    // this->sendMessage<char const>(last_socket, str.c_str(), str.length());
//    write(cliente, str.c_str(), str.size());
//    std::cout << "Mensagem enviada: " << str << std::endl;

//    if (msg.getTipo() == tipoDaMensagem::SAIDA) return; 
//    // close(cliente);
//    }
// }

Loja::Loja(short unsigned int porta, unsigned int qtdAgua, unsigned int qtdCerveja, unsigned int qtdRefrigerante, unsigned int maxClientes)
   : Socket::Server(porta, maxClientes) {
      this->estoque[AGUA] = qtdAgua;
      this->estoque[CERVEJA] = qtdCerveja;
      this->estoque[REFRIGERANTE] = qtdRefrigerante;
      // this->nAguasDisponiveis = qtdAgua;
      // this->nCervejasDisponiveis = qtdCerveja;
      // this->nRefrigerantesDisponiveis = qtdRefrigerante;
   }

Loja::~Loja() {}

// void Loja::answerMessage(void *msg) {

// }

bool Loja::tratarPedido(int bebida, unsigned int quantidade) {
   if (bebida > 2 || quantidade > this->estoque[bebida])
      return false;

   this->estoque[bebida] -= quantidade;
   return true;
}

void Loja::comecarExpediente() {

   int sd, max_sd, activity, new_socket;
   long int valread;
   int addrlen = sizeof(this->_address);
   //   char buffer [1025];
   Mensagem msg;
   std::string message;      

   std::cout << "Waiting for connections ..." << std::endl;
   while(!this->estoqueVazio()) {  
         // Clear console
         // std::cout << "\x1B[2J\x1B[H";
         this->imprimeEstoque();
        //clear the socket set 
        FD_ZERO(&readfds);  
     
        //add master socket to set 
        FD_SET(this->serverFD, &readfds);  
        max_sd = this->serverFD;  
             
        //add child sockets to set 
        for (int i = 0 ; i < this->_maxClients ; i++)  
        {  
            //socket descriptor 
            sd = this->clientsSockets[i];  
                 
            //if valid socket descriptor then add to read list 
            if(sd > 0)  
                FD_SET( sd , &readfds);  
                 
            //highest file descriptor number, need it for the select function 
            if(sd > max_sd)  
                max_sd = sd;  
        }  
     
        //wait for an activity on one of the sockets , timeout is NULL , 
        //so wait indefinitely 
        activity = select( max_sd + 1 , &readfds , NULL , NULL , NULL);  
       
        if ((activity < 0) && (errno!=EINTR))  
        {  
            // printf("select error");  
            std::cout << "select error" << std::endl;
        }  
             
        //If something happened on the master socket, then its an incoming connection 
        if (FD_ISSET(this->serverFD, &readfds))  
        {  
            if ((new_socket = accept(this->serverFD, 
                    (struct sockaddr *)&_address, (socklen_t*)&addrlen))<0)  
            {  
                perror("accept");  
                exit(EXIT_FAILURE);  
            }  
             
            //inform user of socket number - used in send and receive commands 
            // printf("New connection , socket fd is %d , ip is : %s , port : %d\n" , new_socket ,
            //    inet_ntoa(_address.sin_addr) , ntohs(_address.sin_port));  
           
            //send new connection greeting message 

            message = "Seja bem-vindo à loja de bebidas!\n";
            message += "Faça seu pedido digitando o número correspondente à bebida desejada e a quantidade no formato {bebida quantidade}.\n";
            message += "Menu: \n";
            message += "1 -> Água\n";
            message += "2 -> Cerveja\n";
            message += "3 -> Refrigerante\n";
            message += "0 -> Sair da loja\n";
            if( send(new_socket, message.c_str(), message.size(), 0) != (unsigned) message.size() )  
            {  
                perror("send");  
            }  
                 
            // puts("Welcome message sent successfully"); 
            std::cout << "Cliente " << new_socket << " chegou na loja." << std::endl; 
                 
            //add new socket to array of sockets 
            for (int i = 0; i < this->_maxClients; i++)  
            {  
                //if position is empty 
                if( this->clientsSockets[i] == 0 )  
                {  
                    this->clientsSockets[i] = new_socket;  
                    printf("Adding to list of sockets as %d\n" , i);  
                         
                    break;  
                }  
            }  
        }  
        //else its some IO operation on some other socket
        for (int i = 0; i < this->_maxClients; i++)  
        {  
            sd = this->clientsSockets[i];  
                 
            if (FD_ISSET( sd , &(this->readfds)))  
            {  
                //Check if it was for closing , and also read the 
                //incoming message 
                if ((valread = read( sd, &msg, sizeof(Mensagem))) == 0)  
                {  
                    //Somebody disconnected , get his details and print 
                    getpeername(sd , (struct sockaddr*)&_address , (socklen_t*)&addrlen);  
                    printf("Host disconnected , ip %s , port %d \n" , 
                    inet_ntoa(_address.sin_addr) , ntohs(_address.sin_port));  
                         
                    //Close the socket and mark as 0 in list for reuse 
                    close( sd );  
                    this->clientsSockets[i] = 0;  
                }  
                     
                //Echo back the message that came in 
                else 
                {  
                  
                  if (this->tratarPedido(msg.getBebida(), msg.getQuantidade())) {
                     message = "Aqui está seu pedido.\n";
                  } else
                     message = "Seu pedido não pode ser atendido.\n";
                  }

                    //set the string terminating NULL byte on the end 
                    //of the data read 
                    // answerMessage(buffer);
                    this->sendMessage(sd, message.c_str(), message.size());
                    // buffer[valread] = '\0';  
                    // send(sd , buffer , strlen(buffer) , 0 );  
               }  
            }  
        }

        for (int i = 0; i < this->_maxClients; i++)
         if (this->clientsSockets[i] != 0) 
            shutdown(this->clientsSockets[i], SHUT_RDWR);
    }  
   


bool Loja::estoqueVazio() {
   if (this->estoque[AGUA] + this->estoque[CERVEJA] + this->estoque[REFRIGERANTE] == 0)
      return true;
   
   return false;
}

void Loja::imprimeEstoque() {
      std::cout << "===== Estoque =====" << std::endl;
      std::cout << "Agua -> " << this->estoque[AGUA] << std::endl;
      std::cout << "Cerveja -> " << this->estoque[CERVEJA] << std::endl;
      std::cout << "Refrigerante -> " << this->estoque[REFRIGERANTE] << std::endl;
      std::cout << "==================" << std::endl;
}