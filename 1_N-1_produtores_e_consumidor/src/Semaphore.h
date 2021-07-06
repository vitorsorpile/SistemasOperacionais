#ifndef _SEMAPHORE_H
#define _SEMAPHORE_H

#include <condition_variable>

using namespace std;
class Semaphore {
   private:
      unsigned int bufferSize;
      
   public:
      mutex toBeDeliveredMutex;
      mutex toBeProducedMutex;
      mutex bufferMutex;
      mutex semaphoreMutex;
      condition_variable consumer, producer;
      unsigned int buffer = 0;
      unsigned int toBeProduced;
      unsigned int toBeDelivered;

      Semaphore(int bufferSize);
      bool down(unsigned int *buffer);
      bool up(unsigned int *buffer);
      unsigned int getBuffer();
      // unsigned int getConsumed();
      // unsigned int getProduced();
      unsigned int getBufferSize();
};

#endif