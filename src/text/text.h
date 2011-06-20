#ifndef TEXT_H_INCLUDED
#define TEXT_H_INCLUDED

#include <string>
#include <map>
#include "myBox.h"
#include "renderList.h"

class t_text;

class t_textList
{
public:
   t_textList(const t_text &_base);

   void addString(const std::string &text,float x, float y);
   void draw() const;
   void clear();

private:
   const t_text &base;
   t_renderList list;
};

class t_text
{
public:


   t_text(int textSize = 14, bool subpixel = false);
   void drawString(const std::string &text,float x, float y );
   void addString(const std::string &text,float x , float y ,t_renderList &list) const;
   void draw(const t_renderList &list) const;
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

   std::map<char,t_myBox> charLocations;
   std::map<char,glyphMetric> charMetrics;
   int side;
   unsigned int texture;
};



#endif
