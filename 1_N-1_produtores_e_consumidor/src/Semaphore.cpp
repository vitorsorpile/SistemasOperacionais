#include "Semaphore.h"

using namespace std;

Semaphore::Semaphore(int n, int bufferSize) {
   this->toBeProduced = n;
   this->toBeDelivered = n;
   this->_bufferSize = bufferSize;
}

Semaphore::~Semaphore() {}

// Retira um elemento de var
bool Semaphore::down(unsigned int *var) {
   if ((*var) > 0) {
      (*var)--;
      return true;
   }
   return false;
}

// Acrescenta um elemento em var ou retorna falso se o buffer já estiver cheio
bool Semaphore::up(unsigned int *var) {
   if ((*var) == _bufferSize) {
      return false;
   }

   (*var)++;
   return true;
}

unsigned int Semaphore::getBuffer() {
   return this->buffer;
}

unsigned int Semaphore::getBufferSize() {
   return this->_bufferSize;
}
