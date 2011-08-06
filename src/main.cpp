#include <GL/glew.h>

#include <iostream>

#include <boost/format.hpp>
#include <boost/bind.hpp>

#include <SFML/Window.hpp>

#include <gtkmm.h>
#include <gdk/gdkx.h>


#include <text.h>
#include <textList.h>

#include <jsonList.h>
#include <imageJson.h>

#include <render.h>
#include <renderList.h>
#include <imageList.h>

#include <sfmlWidget.h>

#include <pool.h>
using std::cout;
using boost::format;
using boost::bind;
using boost::ref;

class blah
{
public:
   blah(Gtk::DrawingArea &_area) : area(_area), render(), image("../res/pixelPacker.png","../res/pixelPacker.json"),jsonList(render,image), text(20), lazyDogText(render,text), list(render, "../res/blah.png")
   {
   }

   void init()
   {
      app.SetFramerateLimit(60);

      GLenum err = glewInit();

      if (GLEW_OK != err)
      {
         cout<<format("Glew error: %s\n") % glewGetErrorString(err);
         exit(1);
      }

      cout<<format("Status: Using GLEW %s\n") % glewGetString(GLEW_VERSION);
      render.initialize("../res/frag","../res/vert");
      render.setSize(800,800);
      area.set_size_request(800,800);
      render.perspectiveOrtho(0,100,100, 0, -5, 5);

      glClearColor(0,.5,.5,0);

      jsonList.addImage("5",10,10,1);

      lazyDogText.addString("The quick brown fox jumps over a lazy dog",0,50);


      list.addRect(30,30,0,0,0,
                   70,70,0,1,1);
      area.signal_draw().connect(sigc::mem_fun(this,&blah::onDraw));
   }

   bool onDraw(const Cairo::RefPtr < Cairo::Context >&)
   {
      sf::Event event;

      while (app.GetEvent(event))
      {
         switch (event.Type)
         {
         case sf::Event::Resized:
         {
            render.setSize(event.Size.Width,event.Size.Height);

            lazyDogText.clear();
            lazyDogText.addString("The quick brown fox jumps over the lazy dog",0,50);

            jsonList.clear();
            jsonList.addImage("5",10,10,1);
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
      jsonList.draw();

      checkGLError();
      app.Display();
      return true;
   }




   sf::Window app;
private:
   Gtk::DrawingArea &area;
   Render render;
   ImageJson image;
   JsonList jsonList;
   Text text;
   TextList lazyDogText;
   ImageList list;

} ;

void c()
{
   printf("Blah, blah\n");
   sleep(10);
   printf("Blah, blah\n");
}

int main(int argc, char **argv)
{
   Gtk::Main kit(argc,argv);

   Gtk::Window window;
   Gtk::DrawingArea area;

   blah lol(area);

   window.add(area);


   sfmlWidget(lol.app,area,bind(&blah::init,&lol));

   window.show_all();
   kit.run(window);

   printf("Starting threads\n");
   Pool b(4);
   b.addTask(c);
   b.addTask(c);

   return 0;
}
