#include "renderList.h"

#include <GL/glew.h>
#include "glUtil.h"
#include <cstring>

RenderList::RenderList()
{
}
   void RenderList::addPoint(float x, float y, float z, float textX,float textY)
{
   inputData blah;
   memset(&blah,0,sizeof(blah));
   blah.translation[0] = x;
   blah.translation[1] = y;
   blah.translation[2] = z;
   blah.textcord[0] = textX;
   blah.textcord[1] = textY;

   vertices.push_back(blah);

}

void RenderList::addRect(float x1,float y1, float z1, float textX1, float textY1,
                           float x2,float y2, float z2, float textX2, float textY2)
{
   addPoint(x1,y1,z1,textX1,textY1);
   addPoint(x1,y2,z1,textX1,textY2);
   addPoint(x2,y1,z1,textX2,textY1);
   addPoint(x2,y2,z1,textX2,textY2);
}

   void RenderList::draw() const 
{
   glBufferSubData(GL_ARRAY_BUFFER,0, vertices.size() * sizeof(inputData),&vertices[0]);
   checkGLError();

   glDrawElements(GL_TRIANGLES,6 * vertices.size()/4,GL_UNSIGNED_SHORT,0);
   checkGLError();
}

void RenderList::clear()
{
   vertices.clear();
}
