#include "sfmlWidget.h"

#include <SFML/Window.hpp>

#include <gtkmm.h>
#include <gdk/gdkx.h>
#include <boost/function.hpp>

void realizeFunc(sf::Window &App, Gtk::DrawingArea &area, boost::function<void (void)> init);
void sfmlWidget(sf::Window &App,Gtk::DrawingArea &area, const boost::function<void (void)> &init)
{
   area.add_events(Gdk::EventMask::ALL_EVENTS_MASK);
   area.set_can_focus();
   area.set_double_buffered(false);

   area.signal_realize().connect(sigc::bind(&realizeFunc,sigc::ref(App), sigc::ref(area),init));

}

void realizeFunc(sf::Window &App, Gtk::DrawingArea &area, boost::function<void (void)> init)
{
   printf("The window was realized\n");
   auto gwindow = area.get_window();//gwindow is a Glib::RefPtr<Gdk::Window>
    if(gwindow)
      {
	auto xwin = GDK_WINDOW_XID(gwindow ->gobj());
    std::cout<<"on_realize occoured\n";    
    std::cout<<"xwin id: "<<xwin<<"\n";
   App.Create(xwin);
   init();
      }
}

