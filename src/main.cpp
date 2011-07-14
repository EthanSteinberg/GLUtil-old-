#include <GL/glew.h>
#include <iostream>
#include <boost/format.hpp>
#include <SFML/Window.hpp>
#include "text/text.h"
#include "glUtil.h"
#include "matrix.h"
#include "pngUtil.h"
#include "pngList.h"
#include "pngJson.h"
#include "render.h"
#include "renderList.h"

using std::cout;
using boost::format;

struct testing
{
   int b;
   int a;
   friend std::ostream& operator<< (std::ostream& out, testing const& t);

};

std::ostream& operator<< (std::ostream& out, testing const& t)
{
   return out<< format("%d %d") % t.b % t.a;
}

int main(int argv, char **argc)
{
   testing f;
   f.b = 10;
   f.a = 20;
   cout<<format("%d \n") % f;

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
   blah.loadImage("../res/blah.png");
   blah.perspectiveOrtho(0,100,100, 0, -5, 5);

   PngJson image("../res/pixelPacker.png","../res/pixelPacker.json");
   image.setSize(800,600);
   PngList imageList(image);
   imageList.addImage("5",10,10,1);

   Text text(20);
   text.setSize(800,600);
   TextList lazyDogText(text);
   lazyDogText.addString("The quick brown fox jumps over the lazy dog",0,50);

   glClearColor(0,.5,.5,0);

   RenderList list;
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
            image.setSize(event.Size.Width,event.Size.Height);

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
