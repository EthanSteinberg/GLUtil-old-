#include <GL/glew.h>
#include "pngJson.h"
#include <json/json.h>

#include <iostream>
#include <fstream>
#include "pngUtil.h"

#include "glUtil.h"
#include "renderList.h"

t_pngJson::t_pngJson(const std::string &picname, const std::string &jsonName)
{
   root = new Json::Value;
   std::ifstream jsonFile(jsonName);
   Json::Reader reader;
   bool success = reader.parse(jsonFile,*root);

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

void t_pngJson::addImage(const std::string &name,float x, float y,float scale, t_renderList &list) const
{
   Json::Value imageValue = (*root)[name];
   if (imageValue.isNull())
   {
      printf("That image %s is not in the picture\n",name.c_str());
      exit(1);
   }

   
   float sidex = (*root)["sizex"].asInt();
   float sidey = (*root)["sizey"].asInt();

   int imageX = imageValue["x"].asInt();
   int imageY = imageValue["y"].asInt();
   int imageSizeX = imageValue["sizex"].asInt();
   int imageSizeY = imageValue["sizey"].asInt();
   //printf("The size was %d and %d",imageSizeX,imageSizeY);

   //list.addRect(x, y, 0,0,0,
     //           x + imageSizeX/scale,y + imageSizeY/scale,0,1,1);
     //

   const float translateX = (imageSizeX/scale)/width;
   const float translateY = (imageSizeY/scale)/height;
   //printf("The translate is %f\n",translateX);

   list.addRect(x, y, 0,imageX/sidex,(imageY + imageSizeY)/sidey,
                x + 100 * translateX,y + 100 * translateY,0,(imageX + imageSizeX)/sidex,imageY/sidey);
}

void t_pngJson::draw(const t_renderList &list) const
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

void t_pngJson::setSize(int _width, int _height)
{
   width = _width;
   height = _height;
}


