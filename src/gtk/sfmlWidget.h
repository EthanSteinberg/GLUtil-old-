#ifndef SFML_WIDGET_H_INCLUDED
#define SFML_WIDGET_H_INCLUDED

namespace Gtk
{
   class DrawingArea;
}

namespace sf
{
class Window;
}

#include <boost/function.hpp>

void sfmlWidget(sf::Window &App,Gtk::DrawingArea &area, const boost::function<void (void)> &init);



#endif
