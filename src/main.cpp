#include <GL/glew.h>
#include <cstdio>
#include <SFML/Window.hpp>
#include "text/text.h"
#include "glUtil.h"
#include "matrix.h"
#include "pngUtil.h"
#include "render.h"
#include "renderList.h"

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
   t_render blah("../res/frag","../res/vert");
   blah.loadImage("../res/blah.png");
   blah.perspectiveOrtho(0,100,100, 0, -5, 5);

   t_text text(20);
   text.setSize(800,600);
   t_textList lazyDogText(text);
   lazyDogText.addString("The quick brown fox jumps over the lazy dog",0,50);

   glClearColor(0,.5,.5,0);

   t_renderList list;
   list.addRect(  30,30,0,0,0,
                  70,70,0,1,1);

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
   
      list.draw();
      lazyDogText.draw();

      checkGLError();
      App.Display();
   }
}
