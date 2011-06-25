#ifndef TEXH_INCLUDED
#define TEXH_INCLUDED

#include <string>
#include <map>
#include "myBox.h"
#include "renderList.h"

class Text;

class TextList
{
public:
   TextList(const Text &_base);

   void addString(const std::string &text,float x, float y);
   void draw() const;
   void clear();

private:
   const Text &base;
   RenderList list;
};

class Text
{
public:


   Text(int textSize = 14, bool subpixel = false);
   void drawString(const std::string &text,float x, float y );
   void addString(const std::string &text,float x , float y ,RenderList &list) const;
   void draw(const RenderList &list) const;
   void setSize(int width, int height);

private:

   int width;
   int height;

   struct glyphMetric
   {
      double width;
      double height;
      double advance;
      double bearingX;
      double bearingY;

      void raster(int _width,int _height)
      {
         width/=_width;
         height/= _height;

         advance /= _width;

         bearingX /= _width;
         bearingY /= _height;
      }
   };

   std::map<char,MyBox> charLocations;
   std::map<char,glyphMetric> charMetrics;
   int side;
   unsigned int texture;
};



#endif
