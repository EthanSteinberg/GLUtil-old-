#ifndef PNG_JSON_H_INCLUDED
#define PNG_JSON_H_INCLUDED

#include <string>


class t_renderList;

namespace Json
{
   class Value;
}

class t_pngJson
{
public:
   t_pngJson(const std::string &filename, const std::string &jsonname);
   void addImage(const std::string &text,float x , float y ,float scale,t_renderList &list) const;
   void draw(const t_renderList &list) const;
   void setSize(int width, int height);

private:
   int width;
   int height;
   unsigned int texture;
   Json::Value *root;
};


#endif
