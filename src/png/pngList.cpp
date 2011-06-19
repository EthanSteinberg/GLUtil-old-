#include <GL/glew.h>
#include "pngList.h"
#include <json/json.h>

#include <iostream>
#include <fstream>
#include "pngUtil.h"

#include "glUtil.h"

t_pngList::t_pngList(const std::string &picname, const std::string &jsonName)
{
   std::ifstream jsonFile(jsonName);
   Json::Reader reader;
   bool success = reader.parse(jsonFile,root);

   if (!success)
   {
      std::cout <<"Failed to parse\n"<<reader.getFormatedErrorMessages();
      exit(1);
   }

   int lastTexture;
   glGetIntegerv(GL_TEXTURE_BINDING_2D,&lastTexture);
   checkGLError();

   glGenTextures(1,&texture);
   checkGLError();

   glBindTexture(GL_TEXTURE_2D,texture);
   checkGLError();

   loadTexture(picname);

   glBindTexture(GL_TEXTURE_2D,lastTexture);
   checkGLError();
}

void t_pngList::addImage(const std::string &name,float x, float y,float scale)
{
   Json::Value imageValue = root[name];
   if (imageValue.isNull())
   {
      printf("That image %s is not in the picture\n",name.c_str());
      exit(1);
   }

   
   float sidex = root["sizex"].asInt();
   float sidey = root["sizey"].asInt();

   int imageX = imageValue["x"].asInt();
   int imageY = imageValue["y"].asInt();
   int imageSizeX = imageValue["sizex"].asInt();
   int imageSizeY = imageValue["sizey"].asInt();
   printf("The size was %d and %d",imageSizeX,imageSizeY);

   //list.addRect(x, y, 0,0,0,
     //           x + imageSizeX/scale,y + imageSizeY/scale,0,1,1);

   list.addRect(x, y, 0,imageX/sidex,(imageY + imageSizeY)/sidey,
                x + imageSizeX/scale,y + imageSizeY/scale,0,(imageX + imageSizeX)/sidex,imageY/sidey);
}

void t_pngList::draw() const
{
   int lastTexture;
   glGetIntegerv(GL_TEXTURE_BINDING_2D,&lastTexture);
   checkGLError();

   glBindTexture(GL_TEXTURE_2D,texture);
   checkGLError();

   list.draw();
   
   glBindTexture(GL_TEXTURE_2D,lastTexture);
   checkGLError();
}

void t_pngList::clear()
{
   list.clear();
}
