#include "imageList.h"

#include <iostream>
#include <boost/format.hpp>


#include "render.h"
using std::cout;
using boost::format;

ImageList::ImageList(Render &render, const std::string &picname) : list(render), filename(picname)
{
}


void ImageList::draw() const
{

   list.renderer.loadImage(filename);

   list.draw();

}

void ImageList::clear()
{
   list.clear();
}
void ImageList::addPoint(float x, float y, float z, float textX,float textY)
{
   list.addPoint(x,y,z,textX,textY);
}
void ImageList::addRect(float x1,float y1, float z1, float textX1, float textY1,
                        float x2,float y2, float z2, float textX2, float textY2)
{
   list.addRect(x1,y1,z1,textX1,textY1,x2,y2,z2,textX2,textY2);
}
