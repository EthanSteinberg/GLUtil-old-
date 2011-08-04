#ifndef TEXT_LIST_H_INCLUDED
#define TEXT_LIST_H_INCLUDED

class Text;
class Render;
#include "renderList.h"

class TextList
{
public:
   TextList(Render &render,const Text &_base);

   void addString(const std::string &text,float x, float y);
   void draw() const;
   void clear();

private:
   const Text &base;
   RenderList list;
};

#endif
