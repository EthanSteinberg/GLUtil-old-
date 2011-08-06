#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

#include "message.h"

class Queue
{
public:
   Queue();
   Queue(const Queue &other);

   ~Queue();

   void push(const Message &message);

   void closeRead();
   void closeWrite();

   int getWaitFd() const; //get the file descriptor used for waiting on me
   Message pop();


private:
   int fds[2];

};

#endif
