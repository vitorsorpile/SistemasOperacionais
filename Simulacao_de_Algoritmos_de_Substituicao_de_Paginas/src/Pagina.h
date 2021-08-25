#ifndef _PAGINA_H
#define _PAGINA_H

#include <vector>
#include <limits>

class Pagina {
   unsigned int _id;
   unsigned int movidaPraRAM;
   mutable unsigned int ultimoAcesso;
   mutable unsigned int indexProximoAcesso = 0;
   // unsigned int proximoAcesso;


   public:
   mutable std::vector<unsigned int> ordemDeAcessos;
      Pagina(unsigned int id);
      // Pagina(const Pagina&);
      ~Pagina();

      void setUltimoAcesso(unsigned int instante) const;
      void addAcessoFuturo(unsigned int instante) const;
      void increaseIndexProximoAcesso() const;

      unsigned int getId() const;
      unsigned int getUltimoAcesso() const;
      unsigned int getProximoAcesso() const;
      
      
      bool operator==(const Pagina& o) const;
      class HashFunction {
         public:
         std::size_t operator()(const Pagina pagina) const {
            return std::hash<int>()(pagina._id);
         }
      };


};

#endif