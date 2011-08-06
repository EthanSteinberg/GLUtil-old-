#include "imageJson.h"
#include <json/json.h>

#include <iostream>
#include <boost/format.hpp>

using std::cout;
using boost::format;

#include <fstream>


ImageJson::ImageJson(const std::string &picname, const std::string &jsonName) : filename(picname)
{
   root = new Json::Value;
   std::ifstream jsonFile(jsonName);
   Json::Reader reader;
   bool success = reader.parse(jsonFile,*root);

   if (!success)
   {
      cout <<format("Failed to parse %s\n")  % reader.getFormatedErrorMessages();
      exit(1);
   }
}


const Json::Value* ImageJson::getRoot() const
{
   return root;
}

const std::string & ImageJson::getFilename() const
{
   return filename;
}



