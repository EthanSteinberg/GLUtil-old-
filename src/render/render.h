#ifndef RENDER_H_INCLUDED
#define RENDER_H_INCLUDED

#include <string>
#include <map>
#include <vector>

#include "glUtil.h"


class Render
{
public:
   Render(const std::string &frag, const std::string &vert, int numOfRects = 100);
   void loadImage(const std::string &filename);
   void perspectiveOrtho(double left,double right,double bottom, double top, double near, double far);
   void setTextRenderMode(bool mode);
   void drawVertices(const std::vector<inputData> &vertices);
   int width;
   int height;

private:

   unsigned int textRenderModePosition;
   
   unsigned int program;
   void createAndBindBuffers(int numOfRects);
   void bindTexture();
   std::map<std::string,int> textMap;
};


#endif
