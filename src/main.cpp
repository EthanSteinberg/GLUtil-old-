#include <GL/glew.h>
#include <cstdio>
#include <SFML/Window.hpp>




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
      App.Display();
   }
}
