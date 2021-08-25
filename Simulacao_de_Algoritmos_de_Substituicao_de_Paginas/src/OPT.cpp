#include "OPT.h"

OPT::OPT(unsigned int quadros, std::unordered_set<Pagina, Pagina::HashFunction> *paginas) 
   : paginasNaRAM(quadros, nullptr) 
{
   this->_quadros = quadros;
   this->quadrosDisponiveis = quadros;
   this->_paginas = paginas;
   // this->_paginas = paginas;
}

OPT::~OPT() {}

// void OPT::executar() {
//    auto i = std::max_element(this->_paginas.begin(), this->_paginas.end());
//    std::cout << "max: " << *i << std::endl;
// }

void OPT::acessarPagina(const Pagina* pagina/*, int instante*/) {
   // static unsigned int pos = 0;
   // Página já está na RAM
   // std::cout << "recebeu pagina: " << pagina << std::endl;
   
   //  for (auto& pag: this->paginasNaRAM)
   //       std::cout << pag->getId() << " ";

   //    std::cout << std::endl;

   if (std::find(this->paginasNaRAM.begin(), this->paginasNaRAM.end(), pagina) != this->paginasNaRAM.end()) {
      // std::cout << "pagina ja estava na RAM" << std::endl;
      pagina->increaseIndexProximoAcesso();
      return;
   }

   faltasDePagina++;
   // std::cout << "Faltou pagina: " << pagina << std::endl;
   // Existem quadros dísponíveis

   if (quadrosDisponiveis != 0) {
      this->paginasNaRAM[this->paginasNaRAM.size() - quadrosDisponiveis] = pagina;
      quadrosDisponiveis--;
      pagina->increaseIndexProximoAcesso();
      // for (auto& pag: this->paginasNaRAM)
      //    std::cout << pag->getId() << " ";

      // std::cout << std::endl;
      // pos++;
      return;
   }

   auto it = std::max_element(paginasNaRAM.begin(), paginasNaRAM.end(),
                             []( const Pagina *a, const Pagina *b )
                             {   
                              //   std::cout << "a: " << a->getUltimoAcesso() << " | b: " << b->getUltimoAcesso() << std::endl; 
                                 return a->getProximoAcesso() < b->getProximoAcesso();
                             } );
   // std::cout << "instante "  << instante << " -> " << (*it)->getId() << " trocado pelo " << pagina->getId() << " que tem proximo acesso em " << (*it)->getProximoAcesso() << std::endl;  
   // std::cout << min - paginasNaRAM.begin() << std::endl;
   this->paginasNaRAM[it - paginasNaRAM.begin()] = pagina;
   pagina->increaseIndexProximoAcesso();
   // for (auto& pag: this->paginasNaRAM)
   //       std::cout << pag->getId() << " ";

   //    std::cout << std::endl;
   return;
   // Todos os quadros estão ocupados'
   // pos++;
   // if (pos >= this->_quadros) pos = 0;
   // this->paginasNaRAM[pos] = pagina;
   
}


unsigned int OPT::getFaltasDePagina() {
   return this->faltasDePagina;
}