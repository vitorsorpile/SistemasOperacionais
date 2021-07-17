#include <thread>
#include <iostream>

class Pessoa : public std::thread {
   private:
      void behavior();
      int _id;

   public:
      Pessoa(int pessoaId);
      ~Pessoa();

   static void threadFunction(Pessoa *This);
};