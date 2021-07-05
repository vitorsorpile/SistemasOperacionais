#include "Semaphore.h"

using namespace std;

Semaphore::Semaphore(int bufferSize) {
   this->bufferSize = bufferSize;
   this->toBeProduced = bufferSize;
}

// Retira um elemento do buffer
bool Semaphore::down(unsigned int *buffer) {
   if ((*buffer) > 0) {
      (*buffer)--;
      return true;
   }
   producer.notify_one();
   return false;
}

// Acrescenta um elemento no buffer
bool Semaphore::up(unsigned int *buffer) {
   if ((*buffer) == bufferSize) {
      // producer.notify_all();
      return false;
   }

   (*buffer)++;
   if ((*buffer) == 1) {
      consumer.notify_one();
   }
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
