#include "render.h"

#include "glUtil.h"
#include <GL/glew.h>
#include <iostream>
#include <boost/format.hpp>

#include <vector>
#include "imageUtil.h"
#include "matrix.h"

#include "renderList.h"

#include <cassert>


inline
void *offset(int floatNum)
{
   return (void *)(sizeof(float) * floatNum);
}

void Render::setClearColor(float red,float green, float blue, float alpha)
{
   glClearColor(red,green,blue,alpha);
}

void Render::clear()
{
   glClear(GL_COLOR_BUFFER_BIT);
}

int Render::getWidth() const
{
   return width;
}

int Render::getHeight() const
{
   return height;
}

void Render::setSize(int _width,int _height)
{
   assert(initialized);

   width = _width;
   height = _height;

   glViewport(0,0,_width, _height);

}

Render::Render() : initialized(false)
{}

void Render::createAndBindBuffers(int numOfRects)
{

   unsigned int buffers[2];

   glGenBuffers(2,buffers);
   checkGLError();

   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,buffers[1]);
   checkGLError();

   std::vector<unsigned short> indexes(6 * numOfRects);

   for (int l = 0; l < 6 * numOfRects; l++)
   {
      int b  = l % 6;
      int c = l/6;

      if (b < 3)
      {
         indexes[l] = b + c * 4;
      }

      else
      {
         indexes[l] = b -2 + c * 4;
      }
   }


   glBufferData(GL_ELEMENT_ARRAY_BUFFER,6 * numOfRects * sizeof(short),&indexes[0],GL_STATIC_DRAW);
   checkGLError();


   glBindBuffer(GL_ARRAY_BUFFER,buffers[0]);
   checkGLError();

   glBufferData(GL_ARRAY_BUFFER,4 * numOfRects * sizeof(inputData),NULL,GL_STREAM_DRAW);
   checkGLError();

   glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(inputData) ,offset(0));
   checkGLError();
   glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,sizeof(inputData) ,offset(3));
   checkGLError();
   glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,sizeof(inputData) ,offset(6));
   checkGLError();
   glVertexAttribPointer(3,1,GL_FLOAT,GL_FALSE,sizeof(inputData) ,offset(8));
   checkGLError();

   glEnableVertexAttribArray(0);
   checkGLError();
   glEnableVertexAttribArray(1);
   checkGLError();
   glEnableVertexAttribArray(2);
   checkGLError();
   glEnableVertexAttribArray(3);
   checkGLError();

   glBindAttribLocation(program,0,"in_Position");
   checkGLError();

   glBindAttribLocation(program,1,"in_Translation");
   checkGLError();

   glBindAttribLocation(program,2,"in_TextCord");
   checkGLError();

   glBindAttribLocation(program,3,"in_ZRotation");
   checkGLError();

}

void Render::initialize(const std::string &frag, const std::string &vert, int numOfRects)
{
   initialized = true;
   GLenum err = glewInit();

      if (GLEW_OK != err)
      {
         std::cout<<boost::format("Glew error: %s\n") % glewGetErrorString(err);
         exit(1);
      }

      std::cout<<boost::format("Status: Using GLEW %s\n") % glewGetString(GLEW_VERSION);
   
      GLuint vertShader = createShader(vert, GL_VERTEX_SHADER);
   GLuint fragShader = createShader(frag, GL_FRAGMENT_SHADER);
   program = createProgram(vertShader,fragShader);

   glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
   glEnable(GL_BLEND);


   createAndBindBuffers(numOfRects);
   activateProgram(program);
   bindTexture();
}

Render::Render(const std::string &frag, const std::string &vert, int numOfRects)
{
   initialize(frag,vert,numOfRects);
}

void Render::bindTexture()
{
   glEnable(GL_TEXTURE_2D);
   checkGLError();

   glActiveTexture(GL_TEXTURE0);
   checkGLError();

   int texturePosition = glGetUniformLocation(program,"in_Texture");
   checkGLError();
   glUniform1i(texturePosition,0);
   checkGLError();

   textRenderModePosition = glGetUniformLocation(program,"textRenderMode");
   checkGLError();
   glUniform1i(textRenderModePosition,0);
   checkGLError();
}


void Render::loadImage(const std::string &filename)
{
   assert(initialized);
   if (textMap.count(filename) == 0)
   {
      unsigned int texture;
      glGenTextures(1,&texture);
      checkGLError();

      glBindTexture(GL_TEXTURE_2D,texture);
      checkGLError();

      loadTexture(filename);
      textMap[filename] = texture;
   }

   else
   {
      glBindTexture(GL_TEXTURE_2D,textMap[filename]);
      checkGLError();
   }
}
void Render::perspectiveOrtho(double left,double right,double bottom, double top, double near, double far)
{
   assert(initialized);
   int perspectivePosition = glGetUniformLocation(program,"in_ProjectionMatrix");
   checkGLError();

   float matrix[16] = {};
   makeOrtho(left,right,bottom,top,near,far,matrix);

   glUniformMatrix4fv(perspectivePosition,1,false,matrix);
   checkGLError();
}

void Render::setTextRenderMode(bool mode)
{
   assert(initialized);
   glUniform1i(textRenderModePosition,mode);
   checkGLError();
}

  void Render::drawVertices(const std::vector<inputData> &vertices)
{
   assert(initialized);
   glBufferSubData(GL_ARRAY_BUFFER,0, vertices.size() * sizeof(inputData),&vertices[0]);
   checkGLError();

   glDrawElements(GL_TRIANGLES,6 * vertices.size()/4,GL_UNSIGNED_SHORT,0);
   checkGLError();
}

