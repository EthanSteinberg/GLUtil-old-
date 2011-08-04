#include "textList.h"
#include "text.h"
#include "render.h"

TextList::TextList(Render &render, const Text &_base) : base(_base), list(render)
{}

void TextList::addString(const std::string &text,float x, float y)
{
   for (unsigned int i = 0; i < text.length(); i++)
   {
      char ch = text[i];
      MyBox box =  base.charLocations.find(ch)->second;
      Text::glyphMetric blah = base.charMetrics.find(ch)->second;
      //cout<<"The with was %lf and %lf\n",blah.width,blah.height);

      blah.raster(list.renderer.width,list.renderer.height);

      x+= 100 * blah.bearingX;
      y-= 100 * (blah.height - blah.bearingY);

      list.addRect(x,y,0,(float) box.pos.x/base.side, (float) box.pos.y/base.side,
                   x+ 100 * blah.width,y + 100 * blah.height,0, (float)(box.pos.x + box.size.x)/base.side, (float)(box.pos.y + box.size.y)/base.side);

      x+= 100 * (blah.advance - blah.bearingX);
      y+= 100 * (blah.height - blah.bearingY);
   }
}
void TextList::draw() const 
{
   list.renderer.loadImage(base.getFilename());
   list.renderer.setTextRenderMode(1);

   list.draw();

   list.renderer.setTextRenderMode(0);
}
void TextList::clear()
{
   list.clear();
}
