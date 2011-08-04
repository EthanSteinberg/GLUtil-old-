#ifndef JSON_LIST_H_INCLUDED
#define JSON_LIST_H_INCLUDED

#include "renderList.h"

class ImageJson;

class JsonList
{

public:
   JsonList(Render &render,const ImageJson &_base);

   void addImage(const std::string &name,float x, float y,float scale);

   void draw() const;
   void clear();

private:
   const ImageJson &base;
   RenderList list;
};

#endif
