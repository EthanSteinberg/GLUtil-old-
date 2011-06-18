#ifndef TEXT_H_INCLUDED
#define TEXT_H_INCLUDED

#include <string>
#include <map>
#include "myBox.h"

class t_text
{
public:
   t_text(int textSize = 14, bool subpixel = false);
   void drawString(const std::string &text = std::string("A"),float x = 50, float y =50);
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
   unsigned int textures[1];
};



#endif
