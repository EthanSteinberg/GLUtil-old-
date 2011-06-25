#include <GL/glew.h>
#include "pngList.h"
#include <json/json.h>

#include <iostream>
#include <fstream>
#include "pngUtil.h"

#include "glUtil.h"

PngList::PngList(const PngJson &_base) : base(_base)
{
}

void PngList::addImage(const std::string &name,float x, float y,float scale)
{
   base.addImage(name,x,y,scale,list);
}

void PngList::draw() const
{
   base.draw(list);
}

void PngList::clear()
{
   list.clear();
}
