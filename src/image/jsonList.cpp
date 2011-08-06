#include "jsonList.h"

#include "imageJson.h"

#include <iostream>
#include <boost/format.hpp>

#include <json/json.h>

#include "render.h"
using std::cout;
using boost::format;

JsonList::JsonList(Render &render,const ImageJson &_base) : base(_base),list(render)
{
}

void JsonList::addImage(const std::string &name,float x, float y,float scale)
{
   const Json::Value *root = base.getRoot();
   Json::Value imageValue = (*root)[name];

   if (imageValue.isNull())
   {
      cout<<format("That image %s is not in the picture\n") % name;
      exit(1);
   }


   float sidex = (*root)["sizex"].asInt();
   float sidey = (*root)["sizey"].asInt();

   int imageX = imageValue["x"].asInt();
   int imageY = imageValue["y"].asInt();
   int imageSizeX = imageValue["sizex"].asInt();
   int imageSizeY = imageValue["sizey"].asInt();
   //cout<<"The size was %d and %d",imageSizeX,imageSizeY);

   //list.addRect(x, y, 0,0,0,
   //           x + imageSizeX/scale,y + imageSizeY/scale,0,1,1);
   //

   const float translateX = (imageSizeX/scale)/list.renderer.getWidth();
   const float translateY = (imageSizeY/scale)/list.renderer.getHeight();
   //cout<<"The translate is %f\n",translateX);

   list.addRect(x, y, 0,imageX/sidex,(imageY + imageSizeY)/sidey,
                x + 100 * translateX,y + 100 * translateY,0,(imageX + imageSizeX)/sidex,imageY/sidey);
}

void JsonList::draw() const
{

   list.renderer.loadImage(base.getFilename());

   list.draw();
   
}

void JsonList::clear()
{
   list.clear();
}
