#ifndef RENDER_H_INCLUDED
#define RENDER_H_INCLUDED

#include <string>
#include <map>


class t_render
{
public:
   t_render(const std::string &frag, const std::string &vert, int numOfRects = 100);
   void loadImage(const std::string &filename);
   void perspectiveOrtho(double left,double right,double bottom, double top, double near, double far);

private:

   unsigned int program;
   void createAndBindBuffers(int numOfRects);
   void bindTexture();
   std::map<std::string,int> textMap;
};


#endif
