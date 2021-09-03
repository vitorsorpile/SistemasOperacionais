#ifndef _PAGINA_H
#define _PAGINA_H

#include <vector>
#include <limits>

// Classe responsável por representar uma página, possui variáveis e métodos que permitem saber quando a página foi
// acessada pela última vez e quando será acessada novamente.
class Pagina {
   unsigned int _id;                                  // ID da página
   mutable unsigned int ultimoAcesso;                 // Último instante em que a página foi acessada
   mutable unsigned int indexProximoAcesso = 0;       // Índice do vector ordemDeAcessos em que está o próximo instante que a página será acessada 
   mutable std::vector<unsigned int> ordemDeAcessos;  // Vector que armazena os instantes em que a página será acessada

   public:
      // Construtor e Destrutor
      Pagina(unsigned int id);
      ~Pagina();

      // Adiciona um instante em que a página será acessada para que sejá possível implementar o algoritmo ótimo
      void addAcessoFuturo(unsigned int instante) const;
      // Aumenta o índice de acesso ao vector ordemDeAcessos para otimizar a execução do algoritmo ótimo
      void increaseIndexProximoAcesso() const;

      // SETs
      void setUltimoAcesso(unsigned int instante) const;

      // GETs
      unsigned int getId() const;
      unsigned int getUltimoAcesso() const;
      // Retorna o instante do próximo acesso ou o maior unsigned int possível caso a página já tenha sido acessada todas as vezes
      unsigned int getProximoAcesso() const;
      
      // Sobrecarga de operador e classe interna para fazer hash, são usadas para permitir o uso da estrutura de dados
      // unordered_set, que foi utilizada para otimizar a execução do algoritmo ótimo
      bool operator==(const Pagina& o) const;
      class HashFunction {
         public:
         std::size_t operator()(const Pagina pagina) const {
            return std::hash<int>()(pagina._id);
         }
      };
};

#endif