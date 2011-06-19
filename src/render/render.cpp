#include "render.h"

#include "glUtil.h"
#include <GL/glew.h>

#include <vector>
#include "pngUtil.h"
#include "matrix.h"

inline
void *offset(int floatNum)
{
   return (void *)(sizeof(float) * floatNum);
}

void t_render::createAndBindBuffers(int numOfRects)
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

t_render::t_render(const std::string &frag, const std::string &vert, int numOfRects)
{

   GLuint vertShader = createShader(vert, GL_VERTEX_SHADER);
   GLuint fragShader = createShader(frag, GL_FRAGMENT_SHADER);
   program = createProgram(vertShader,fragShader);

   glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
   glEnable(GL_BLEND);


   createAndBindBuffers(numOfRects);
   activateProgram(program);
   bindTexture();
}

void t_render::bindTexture()
{
   glEnable(GL_TEXTURE_2D);
   checkGLError();

   glActiveTexture(GL_TEXTURE0);
   checkGLError();

   int texturePosition = glGetUniformLocation(program,"in_Texture");
   checkGLError();
   glUniform1i(texturePosition,0);
   checkGLError();
}


void t_render::loadImage(const std::string &filename)
{
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
void t_render::perspectiveOrtho(double left,double right,double bottom, double top, double near, double far)
{
   int perspectivePosition = glGetUniformLocation(program,"in_ProjectionMatrix");
   checkGLError();

   float matrix[16] = {};
   makeOrtho(0,100,100,0,-5,5,matrix);

   glUniformMatrix4fv(perspectivePosition,1,false,matrix);
   checkGLError();
}