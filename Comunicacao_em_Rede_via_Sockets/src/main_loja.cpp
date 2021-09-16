
// #include "Socket.h"
#include "Loja.h"
#include <thread>
#include <vector>

int main(int argc, char const *argv[])
{
   if (argc < 5) {
      std::cout << "Número inválido de argumentos.\n";
      std::cout << "Uso: ./servidor PORTA N_AGUAS N_CERVEJAS N_REFRIGERANTES" << std::endl;
      return -1;
   }

   int porta = std::stoi (argv[1]);
   int qtdAguas = std::stoi(argv[2]);
   int qtdCervejas = std::stoi(argv[3]);
   int qtdRefrigerantes = std::stoi(argv[4]);

   if (porta < 0 || qtdAguas < 0 || qtdCervejas < 0 || qtdRefrigerantes < 0) {
      std::cout << "Nenhum dos valores de entrada pode ser negativo." << std::endl;
      return -1;
   }

   Loja loja( (short unsigned) porta, qtdAguas, qtdCervejas, qtdRefrigerantes );
   loja.comecarExpediente();

   std::cout << "Expediente finalizado." << std::endl;

}

