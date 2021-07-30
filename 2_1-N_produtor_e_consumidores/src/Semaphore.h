#ifndef _SEMAPHORE_H
#define _SEMAPHORE_H

#include <condition_variable>

using namespace std;
class Semaphore {
   private:
      unsigned int _bufferSize;
      
   public:
      mutex toBeDeliveredMutex;
      mutex toBeProducedMutex;
      mutex bufferMutex;
      mutex semaphoreMutex;
      condition_variable consumer, producer;
      unsigned int _buffer = 0;
      unsigned int toBeProduced;
      unsigned int toBeDelivered;

      Semaphore(int n, int bufferSize);
      ~Semaphore();

      bool down(unsigned int *buffer);
      bool up(unsigned int *buffer);
      unsigned int getBuffer();
      unsigned int getBufferSize();
};

#endif