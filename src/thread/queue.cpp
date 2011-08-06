#include "queue.h"

#include <unistd.h>

Queue::Queue()
{
   pipe(fds);
}

Queue::Queue(const Queue &other)
{
   fds[0] = dup(other.fds[0]);
   fds[1] = dup(other.fds[1]);
}

Queue::~Queue()
{
   close(fds[0]);
   close(fds[1]);
}

int Queue::getWaitFd() const
{
   return dup(fds[0]);
}

void Queue::push(const Message &message)
{
   write(fds[1],&message,sizeof(message));
}

Message Queue::pop()
{

   Message message;

   if (read(fds[0],&message,sizeof(message)) == 0)
   {
      message.id = Message::type::closed;
   }

   return message;
}

void Queue::closeRead()
{
   close(fds[0]);
}

void Queue::closeWrite()
{
   close(fds[1]);
}

