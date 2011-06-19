#ifndef PNG_LIST_H_INCLUDED
#define PNG_LIST_H_INCLUDED

#include <string>
#include "renderList.h"

#include <json/json.h>

class t_pngList 
{
public:
   t_pngList(const std::string &filename, const std::string &jsonname);
   void addImage(const std::string &name,float x, float y,float scale);
   void draw() const;
   void clear();

private:
   t_renderList list;
   unsigned int texture;
   Json::Value root;
};


#endif
