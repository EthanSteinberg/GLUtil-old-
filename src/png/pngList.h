#ifndef PNG_LIST_H_INCLUDED
#define PNG_LIST_H_INCLUDED

#include <string>
#include "renderList.h"

class t_pngList 
{
public:
   t_pngList(const std::string &filename);
   void addImage(const std::string &name,float x, float y);
   void draw();
   void clear();

private:
   t_renderList list;
};


#endif
