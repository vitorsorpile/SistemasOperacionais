// Client side C/C++ program to demonstrate Socket programming


#include "Socket.h"
#include "Mensagem.h"

class Cliente: public Socket::Client {
   public:
      Cliente(std::string address, short unsigned int port) 
         : Socket::Client(address, port)
      {
         Mensagem msg(tipoDaMensagem::ENTRADA);
         char buffer[1024] = {0}; 
         std::string str = "dale";
         // this->sendMessage(&msg, sizeof(Mensagem));
         // this->sendMessage(str.c_str(), str.size());
         read( sock , buffer, 1024);
         // std::cout << "valread: " << valread << std::endl;
         std::cout << buffer << std::endl;
      }

      void sair() {
         
      }
};
int main(int argc, char const *argv[])
{

   if (argc < 3) {
      std::cout << "Número inválido de argumentos.\n";
      std::cout << "Uso: ./cliente IP PORTA " << std::endl;
      return -1;
   }

   int porta = std::stoi(argv[2]);
   Cliente cl( argv[1], (short unsigned) porta);
   int pedido, quantidade;
   Mensagem msg;
   long int valread;
   // std::string buffer;
   std::string str;
   char buffer[1024] = {0};
   while (true) {
      std::cin >> pedido;
      if (pedido != 0) {
         std::cin >> quantidade;
         // std::cin >> str;
         msg = Mensagem(tipoDaMensagem::PEDIDO, pedido-1, quantidade);
         // std::cout << msg.getBebida() << " " << msg.getQuantidade() << std::endl;
      } 
      else {
         // msg = Mensagem(tipoDaMensagem::SAIDA);
         str.clear();
         // cl.sendMessage(str.c_str(), 0);
         // read(cl.sock, buffer, 1024);
         // std::cout << buffer << std::endl;
         std::cout << "Obrigado! Volte sempre!" << std::endl;
         break;
      }
      // std::cin >> pedido;
      // msg = Mensagem(tipoDaMensagem::ENTRADA);
      // std::string mensa = "cliente aqui\n";
      cl.sendMessage(&msg, sizeof(Mensagem));
      // cl.sendMessage(str.c_str(), str.size());
      valread = read(cl.sock, buffer, 1024);
      buffer[valread] = '\0';
      std::cout << buffer << std::endl;
   }



    // int sock = 0, valread;
    // struct sockaddr_in serv_addr;
    // char *hello = "Hello from client";
    // Mensagem msg(, 75);

    // char buffer[1024] = {""};
    // if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    // {
    //     printf("\n Socket creation error \n");
    //     return -1;
    // }
   
    // serv_addr.sin_family = AF_INET;
    // serv_addr.sin_port = htons(PORT);
       
    // // Convert IPv4 and IPv6 addresses from text to binary form
    // if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) 
    // {
    //     printf("\nInvalid address/ Address not supported \n");
    //     return -1;
    // }
   
    // if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    // {
    //     printf("\nConnection Failed \n");
    //     return -1;
    // }
    // std::cout << msg.getQuantidade() << std::endl;
    // send(sock , &msg, sizeof(Mensagem) , 0 );
    // printf("Hello message sent\n");
    // valread = read( sock , buffer, 1024);
    // printf("%s\n",buffer );
    // return 0;
}