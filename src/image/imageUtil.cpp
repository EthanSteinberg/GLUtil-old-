#include <GL/glew.h>
#include "util.h"
#include "glUtil.h"
#include <vector>

#include <cstdio>
#include <iostream>
#include <boost/format.hpp>

#define cimg_use_png
#include <CImg.h>

using std::cout;
using boost::format;

using cimg_library::CImg;

void loadTexture(const std::string &filename)
{

   CImg<unsigned char> image(filename.c_str());

   int spectrum = image.spectrum();
   int width = image.width();
   int height = image.height();


   //image.mirror('y');
   CImg<unsigned char> texture(image,false); 

   unsigned char *ptrd = texture.data();
   const unsigned int siz = width*height;

   const unsigned char *ptrs[4];

   for (int i = 0; i< spectrum; i++)
   {
      ptrs[i] = image.data(0,0,0,i);
   }


   for (unsigned int off=0; off<siz; off++)
   {
      for (int i = 0; i< spectrum; i++)
      {
         *(ptrd++)= *(ptrs[i]++);
      }
   }

   unsigned char *data = texture.data();

   switch (spectrum)
   {
   case 1:
      glTexImage2D(GL_TEXTURE_2D,0,GL_LUMINANCE,width,height,0,GL_LUMINANCE,GL_UNSIGNED_BYTE,data);
      break;
   case 3:
      glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,data);
      break;
   case 4:
      glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width,height,0,GL_RGBA,GL_UNSIGNED_BYTE,data);
      break;
   default:

      printf("Fail png color type\n");
      exit(1);
   }

   checkGLError();

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   checkGLError();

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   checkGLError();

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
   checkGLError();

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
   checkGLError();

}
