#ifndef TEXT_H_INCLUDED
#define TEXT_H_INCLUDED

#include <string>
#include <map>
#include "myBox.h"
#include "renderList.h"

class Text
{
public:


   Text(int textSize = 14);

   const std::string& getFilename() const;

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

private:

   std::string filename;


   //unsigned int texture;
   
   //Render &renderer;

};



#endif
