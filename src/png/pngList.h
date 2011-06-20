#ifndef PNG_LIST_H_INCLUDED
#define PNG_LIST_H_INCLUDED

#include <string>
#include "renderList.h"
#include "pngJson.h"


class t_pngList 
{
public:
   t_pngList(const t_pngJson &base);
   void addImage(const std::string &name,float x, float y,float scale);
   void draw() const;
   void clear();

private:
   t_renderList list;
   const t_pngJson &base;
};

#endif
