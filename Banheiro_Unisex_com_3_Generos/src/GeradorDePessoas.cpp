#include "GeradorDePessoas.h"

GeradorDePessoas::GeradorDePessoas(int nPessoas, Banheiro* banheiro, bool nPessoasIgualEntreOsGeneros /*= false*/) 
   :  std::thread(threadFunction, this),
      generator(std::chrono::system_clock::now().time_since_epoch().count()),
      generos(0,2), tempoParaChegar(1,7)
{
   this->_nPessoas = nPessoas;
   this->_banheiro = banheiro;
   this->_nPessoasIgualEntreOsGeneros = nPessoasIgualEntreOsGeneros;
}

GeradorDePessoas::~GeradorDePessoas() {}

void GeradorDePessoas::behavior() {
   // std::this_thread::sleep_for(std::chrono::milliseconds(100));
   int pessoasPorGenero[3] = {0};
   int genero;
   std::vector<std::unique_ptr<Pessoa>> pessoas;
   int tempoMedioDeChegada = 0.0;

   for (int i = 0; i < this->_nPessoas; i++) {
      genero = this->generos(this->generator);
      if (_nPessoasIgualEntreOsGeneros) {
         while (pessoasPorGenero[genero] >= this->_nPessoas/3)
         {
            genero = this->generos(this->generator); 
         }
         pessoasPorGenero[genero]++;
      }
      auto t = tempoParaChegar(generator);
      tempoMedioDeChegada += t;
      std::this_thread::sleep_for(std::chrono::seconds(t));
      // std::cout << "Tempo entre pessoas -> " << t << std::endl;
      pessoas.push_back(std::unique_ptr<Pessoa>(new Pessoa(i+1, (GENEROS) genero, this->_banheiro)));

      genero = this->generos(this->generator);
   }

   for (auto & pessoa : pessoas)
      pessoa->join();


   std::cout << "\nTempo médio de chegada das pessoas: " << tempoMedioDeChegada/_nPessoas << " segundos." << std::endl;
}

void GeradorDePessoas::threadFunction(GeradorDePessoas *This) {
   return This->behavior();
}