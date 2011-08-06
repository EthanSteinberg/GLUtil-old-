#include "pool.h"

#include <unistd.h>
#include <syscall.h>

static void *createThread(void *data)
{
   Pool::threadData *stuff = static_cast<Pool::threadData *>(data);

   boost::function<void(void)> *func;

   for (;;)
   {
      pthread_mutex_lock(stuff->mutex);
      int status = read(stuff->fd,&func,sizeof(func));
      pthread_mutex_unlock(stuff->mutex);

      if (status == 0)
         break;
      
      (*func)();
      delete func;
   }

   printf("eof for me tid = %ld\n", syscall(SYS_gettid));

   delete stuff;

   return NULL;
}

Pool::Pool(int num) : threads(num)
{
   
   pthread_mutex_init(&mutex,NULL);

   pipe(fds);

   for (unsigned int i = 0 ; i < threads.size(); i++)
   {
      threadData *data = new threadData;
      data->fd = fds[0];
      data->mutex = &mutex;

      pthread_create(&(threads[i]),NULL, createThread,data);
   }
}


void Pool::addTask(const boost::function<void(void)> &func)
{
   boost::function<void(void)> *funcPtr = new boost::function<void(void)>(func);
   write(fds[1],&funcPtr,sizeof(funcPtr));
}

Pool::~Pool()
{
   close(fds[1]);
   printf("Starting killing\n");
   
   for (unsigned int i = 0; i< threads.size();i++)
   {
      pthread_join(threads[i],NULL);
   }

   close(fds[0]);
   pthread_mutex_destroy(&mutex);
}
