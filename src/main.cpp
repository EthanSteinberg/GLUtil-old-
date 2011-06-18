#include <GL/glew.h>
#include <cstdio>
#include <SFML/Window.hpp>
#include "text/text.h"
#include "util/glUtil.h"
#include "util/matrix.h"

struct inputData
{
   float position[3];
   float translation[3];
   float textcord[2];
   float rotation;

   float buffer[7];
};

inline
void *offset(int floatNum)
{
   return (void *)(sizeof(float) * floatNum);
}

int main(int argv, char **argc)
{
   sf::Window App(sf::VideoMode(800,600,32),"SFML OpenGL");
   App.SetFramerateLimit(60);

   GLenum err = glewInit();

   if (GLEW_OK != err)
   {
      printf("Glew error: %s\n",glewGetErrorString(err));
      exit(1);
   }

   printf("Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
   GLuint vertShader = createShader("../res/vert", GL_VERTEX_SHADER);
   GLuint fragShader = createShader("../res/frag", GL_FRAGMENT_SHADER);
   GLuint program = createProgram(vertShader,fragShader);

   glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
   glEnable(GL_BLEND);


   unsigned int buffers[2];

   glGenBuffers(2,buffers);
   checkGLError();

   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,buffers[1]);
   checkGLError();

   unsigned short indexes[600] = {};

   for (int l = 0; l < 600; l++)
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


   glBufferData(GL_ELEMENT_ARRAY_BUFFER,600 * sizeof(short),indexes,GL_STATIC_DRAW);
   checkGLError();


   glBindBuffer(GL_ARRAY_BUFFER,buffers[0]);
   checkGLError();

   glBufferData(GL_ARRAY_BUFFER,400 * sizeof(inputData),NULL,GL_STREAM_DRAW);
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

   activateProgram(program);

   int perspectivePosition = glGetUniformLocation(program,"in_ProjectionMatrix");
   checkGLError();

   float matrix[16] = {};
   makeOrtho(0,100,100,0,-5,5,matrix);

   glUniformMatrix4fv(perspectivePosition,1,false,matrix);
   checkGLError();


   int texturePosition = glGetUniformLocation(program,"in_Texture");
   checkGLError();
   glUniform1i(texturePosition,0);
   checkGLError();

   t_text text(20);
   text.setSize(800,600);

   glClearColor(0,.5,.5,0);

   while (App.IsOpened())
   {

      sf::Event event;

      while (App.GetEvent(event))
      {
         switch (event.Type)
         {
         case sf::Event::Resized:
         {
            glViewport(0,0,event.Size.Width, event.Size.Height);
            text.setSize(event.Size.Width,event.Size.Height);
         }
         break;

         case sf::Event::Closed:
            exit(0);
            break;

         default:
            ;
            break;


         }
      }

      glClear(GL_COLOR_BUFFER_BIT);

      text.drawString("The quick brown fox jumps over the lazy dog",0,50);
      checkGLError();
      App.Display();
   }
}
