#ifndef PNG_JSON_H_INCLUDED
#define PNG_JSON_H_INCLUDED

#include <string>


class RenderList;

namespace Json
{
   class Value;
}

class PngJson
{
public:
   PngJson(const std::string &filename, const std::string &jsonname);
   void addImage(const std::string &text,float x , float y ,float scale,RenderList &list) const;
   void draw(const RenderList &list) const;
   void setSize(int width, int height);

private:
   int width;
   int height;
   unsigned int texture;
   Json::Value *root;
};


#endif
