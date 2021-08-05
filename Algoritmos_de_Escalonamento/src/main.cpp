#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

#include "Processo.h"

int main(int argc, char *argv[]) {

   if (argc != 2) {
      std::cout << "Número inválido de argumentos!" << std::endl;
      return -1;
   }

   std::fstream file (argv[1]);

   if (!file.is_open()) {
      std::cout << "Unable to open file" << std::endl; 
      return -1;      
   }

   std::string line;
   int start, space, atributos[3], id = 0;
   std::vector<Processo> processos;

   // Leitura do arquivo com os processos
   while ( std::getline (file,line) )
   {
      start = 0;

      for (int i = 0; i < 3; i++) {   
         atributos[i] = std::stoi(line.substr(start));
         space = line.find_first_of(' ', start);
         start = space + 1;
      }

      // Criação dos processos
      processos.push_back(Processo(id, atributos[0], atributos[1], atributos[2]));
      id++;
   }
   file.close();

   // for (auto & processo : processos) {
   //    std::cout << processo;
   // }
   // std::cout << "--------------------" << std::endl;

   // Ordenação dos processos por data de criação a partir da sobrecarga do operador <
   std::sort(processos.begin(), processos.end());
   for (auto & processo : processos) {
      std::cout << processo;
   }



   // while (processos) {

   //       if (acabou processo)
   //          processos--;
   // }

   

   return 0;
}