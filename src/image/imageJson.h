#ifndef IMAGE_JSON_H_INCLUDED
#define IMAGE_JSON_H_INCLUDED

#include <string>


class RenderList;

namespace Json
{
   class Value;
}

class ImageJson
{
public:
   ImageJson(const std::string &filename, const std::string &jsonname);
   const Json::Value * getRoot() const;
   const std::string& getFilename() const;

private:
   Json::Value *root;

   std::string filename;

};


#endif
