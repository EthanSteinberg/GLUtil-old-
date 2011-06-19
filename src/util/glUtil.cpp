#include "util.h"
#include "glUtil.h"

#include <GL/glew.h>
#include <cstdio>

#if 0
#include <boost/scoped_ptr.hpp>
#include <png.h>
#endif
void checkGLError()
{
   while (true)
   {
      switch (glGetError())
      {
      case GL_NO_ERROR:
         return;

      case GL_INVALID_ENUM:
         printf("GL Invalid enum error\n\n");
         printBacktrace();
         exit(1);
         break;

      case GL_INVALID_VALUE:
         printf("GL Invalid value error\n\n");
         printBacktrace();
         exit(1);
         break;
      case GL_INVALID_OPERATION:
         printf("GL Invalid operation error\n\n");
         printBacktrace();
         exit(1);
         break;
      case GL_STACK_OVERFLOW:
         printf("GL Stack overflow error\n\n");
         printBacktrace();
         exit(1);
         break;
      case GL_STACK_UNDERFLOW:
         printf("GL Stack underflow error\n\n");
         printBacktrace();
         exit(1);
         break;
      case GL_OUT_OF_MEMORY:
         printf("GL Out of memory error\n\n");
         printBacktrace();
         exit(1);
         break;

      case GL_TABLE_TOO_LARGE:
         printf("GL Table too large error\n\n");
         printBacktrace();
         exit(1);
         break;
      }
   }
}

unsigned int createProgram(unsigned int vertShader, unsigned int fragShader)
{
   unsigned int program = glCreateProgram();

   if (!program)
   {
      printf("Create program error ");
      checkGLError();
   }

   glAttachShader(program,vertShader);
   checkGLError();

   glAttachShader(program,fragShader);
   checkGLError();

   return program;
}

void activateProgram(unsigned int program)
{

   glLinkProgram(program);
   checkGLError();

   int param;
   glGetProgramiv(program,GL_LINK_STATUS,&param);
   checkGLError();

   if (param == GL_FALSE)
   {
      printf("Problem linking the program\n");

      glGetProgramiv(program,GL_INFO_LOG_LENGTH,&param);
      checkGLError();

      char *logBuffer = new char[param];

      glGetProgramInfoLog(program,param,NULL,logBuffer);
      checkGLError();
      printf("\n%s\n",logBuffer);


      exit(1);
   }

   glValidateProgram(program);
   checkGLError();

   glGetProgramiv(program,GL_VALIDATE_STATUS,&param);
   checkGLError();

   if (param == GL_FALSE)
   {
      glGetProgramiv(program,GL_INFO_LOG_LENGTH,&param);
      checkGLError();

      char *logBuffer = new char[param];

      glGetProgramInfoLog(program,param,NULL,logBuffer);
      checkGLError();
      printf("\n%s\n",logBuffer);
      printf("Problem validating the program\n");
      exit(1);
   }

   glUseProgram(program);
   checkGLError();

   glGetProgramiv(program,GL_INFO_LOG_LENGTH,&param);
   checkGLError();

   char *logBuffer = new char[param];

   glGetProgramInfoLog(program,param,NULL,logBuffer);
   checkGLError();
   printf("\n%s\n",logBuffer);

}
unsigned int createShader(const std::string &filename, int shaderType)
{
   std::string theFile = loadFile(filename);
   printf("I am loading the shader %s\n",filename.c_str());

   unsigned int shader = glCreateShader(shaderType);
   checkGLError();

   const char *data = theFile.c_str();
   glShaderSource(shader,1,&(data),NULL);
   checkGLError();

   glCompileShader(shader);
   checkGLError();

   int param;
   glGetShaderiv(shader,GL_COMPILE_STATUS,&param);
   checkGLError();

   if (param == GL_FALSE)
   {
      //printf("Your shader failed to compile for some reason\n");
      glGetShaderiv(shader,GL_INFO_LOG_LENGTH,&param);
      checkGLError();

      char *logBuffer = new char[param];

      glGetShaderInfoLog(shader,param,NULL,logBuffer);
      checkGLError();
      //printf("Printing out the log of information...\n\n%s\n",logBuffer);
      printf("\n%s\n",logBuffer);
   }

   return shader;
}


