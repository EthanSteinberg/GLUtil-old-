#ifndef POOL_H_INCLUDED
#define POOL_H_INCLUDED

#include <boost/utility.hpp>
#include <boost/function.hpp>

#include <pthread.h>

class Pool : boost::noncopyable
{
public:
   Pool(int num = 10);
   ~Pool();
   void addTask(const boost::function<void(void)> &func);

   struct threadData
   {
      int fd;
      pthread_mutex_t *mutex;
   };

   
private:
   pthread_mutex_t mutex;
   std::vector<pthread_t> threads;
   int fds[2];

};


#endif
