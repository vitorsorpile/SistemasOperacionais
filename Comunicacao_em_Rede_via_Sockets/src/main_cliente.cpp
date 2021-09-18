#include "Cliente.h"

int main(int argc, char const *argv[])
{

   if (argc < 3) {
      std::cout << "Número inválido de argumentos.\n";
      std::cout << "Uso: ./cliente IP PORTA " << std::endl;
      return -1;
   }

   int porta = std::stoi(argv[2]);

   int pedido[2];
   Cliente cl( argv[1], (short unsigned) porta);
   cl.connectToServer();

   while (true) {
      if (!cl.receberResposta()) {
         // std::cout << "Ocorreu um problema na conexão com o servidor..." << std::endl;
         break;
      }

      std::cin >> pedido[0];
      
      if (pedido[0] == 0) {
         std::cout << "Obrigado! Volte sempre!" << std::endl;
         break;
      }

      std::cin >> pedido[1];

      cl.fazerPedido(pedido);
   }
}