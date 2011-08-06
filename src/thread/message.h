#ifndef MESSAGE_H_INCLUDED
#define MESSAGE_H_INCLUDED

#include <cstddef>

struct Message
{
public:

   enum class type
   {
      none = 0,
      closed,
      string,
      gameOpened,
      startMoveArray,
      keyPressed,
      keyReleased,
      mouseMoved
   } id;

   void *data;


private:

};


#endif
