#ifndef PNG_LISH_INCLUDED
#define PNG_LISH_INCLUDED

#include <string>
#include "renderList.h"
#include "pngJson.h"


class PngList 
{
public:
   PngList(const PngJson &base);
   void addImage(const std::string &name,float x, float y,float scale);
   void draw() const;
   void clear();

private:
   RenderList list;
   const PngJson &base;
};

#endif
