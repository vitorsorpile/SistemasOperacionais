#include "Semaphore.h"

using namespace std;

// TODO - ACRESCENTAR toBeProduced NO CONSTRUTOR
Semaphore::Semaphore(int bufferSize) {
   this->bufferSize = bufferSize;
   this->toBeProduced = bufferSize;
   this->toBeDelivered = bufferSize;
}

// Retira um elemento de var
bool Semaphore::down(unsigned int *var) {
   if ((*var) > 0) {
      (*var)--;
      return true;
   }
   // producer.notify_one();
   return false;
}

// Acrescenta um elemento em var
bool Semaphore::up(unsigned int *var) {
   if ((*var) == bufferSize) {
      // producer.notify_all();
      return false;
   }

   (*var)++;
   // if ((*var) == 1) {
   //    consumer.notify_one();
   // }
   return true;
}

unsigned int Semaphore::getBuffer() {
   return this->buffer;
}

// unsigned int Semaphore::getProduced() {
//    return this->produced;
// }

// unsigned int Semaphore::getConsumed() {
//    return this->consumed;
// }

unsigned int Semaphore::getBufferSize() {
   return this->bufferSize;
}
