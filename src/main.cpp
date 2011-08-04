#include <GL/glew.h>
#include <iostream>
#include <boost/format.hpp>
#include <SFML/Window.hpp>
#include "text/text.h"
#include "text/textList.h"
#include "glUtil.h"
#include "matrix.h"
#include "jsonList.h"
#include "imageJson.h"
#include "render.h"
#include "renderList.h"
#include "imageList.h"

using std::cout;
using boost::format;


int main(int argv, char **argc)
{
   sf::Window App(sf::VideoMode(800,600,32),"SFML OpenGL");
   App.SetFramerateLimit(60);

   GLenum err = glewInit();

   if (GLEW_OK != err)
   {
      cout<<format("Glew error: %s\n") % glewGetErrorString(err);
      exit(1);
   }

   cout<<format("Status: Using GLEW %s\n") % glewGetString(GLEW_VERSION);
   Render blah("../res/frag","../res/vert");
   blah.width = 800;
   blah.height = 600;
   blah.perspectiveOrtho(0,100,100, 0, -5, 5);

   ImageJson image("../res/pixelPacker.png","../res/pixelPacker.json");
   JsonList imageList(blah,image);
   imageList.addImage("5",10,10,1);

   Text text(20);
   TextList lazyDogText(blah,text);
   lazyDogText.addString("The quick brown fox jumps over a lazy dog",0,50);

   glClearColor(0,.5,.5,0);

   ImageList list(blah,"../res/blah.png");
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
            blah.width  = event.Size.Width;
            blah.height = event.Size.Height;

            lazyDogText.clear();
            lazyDogText.addString("The quick brown fox jumps over the lazy dog",0,50);

            imageList.clear();
            imageList.addImage("5",10,10,1);
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
      imageList.draw();

      checkGLError();
      App.Display();
   }
}
