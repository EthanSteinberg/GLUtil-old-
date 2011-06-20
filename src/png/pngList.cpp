#include <GL/glew.h>
#include "pngList.h"
#include <json/json.h>

#include <iostream>
#include <fstream>
#include "pngUtil.h"

#include "glUtil.h"

t_pngList::t_pngList(const t_pngJson &_base) : base(_base)
{
}

void t_pngList::addImage(const std::string &name,float x, float y,float scale)
{
   base.addImage(name,x,y,scale,list);
}

void t_pngList::draw() const
{
   base.draw(list);
}

void t_pngList::clear()
{
   list.clear();
}
