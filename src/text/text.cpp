#include "text.h"
#include "myVector2.h"
#include "render.h"
#include "algoMaxRects.h"

#include <iostream>
#include <boost/format.hpp>

using std::cout;
using boost::format;

#include <ft2build.h>

#include <CImg.h>
using namespace cimg_library;

#include "distanceMap.h"

const int padding = 1;

#include FT_FREETYPE_H
#include FT_GLYPH_H
void checkFaceFlags(long faceFlags);

template <class T>
T nexthigher(T k)
{
   k--;

   for (unsigned int i=1; i<sizeof(T)*8; i<<=1)
   {
      k = k | k >> i;
   }

   return k+1;
}


const std::string &Text::getFilename() const
{
   return filename;
}

Text::Text(int textSize)
{
   FT_Library lib;
   int error = FT_Init_FreeType(&lib);

   if (error)
   {
      cout<<"An error in loading the library\n";
      exit(0);
   }

   FT_Face face;
   error = FT_New_Face(lib,"../res/DejaVuSans.ttf",0,&face);

   if (error)
   {
      cout<<"An error in loading the face\n";
      exit(0);
   }


   //long faceFlags = face->face_flags;
   //checkFaceFlags(faceFlags);

   //int emUnits = face->units_per_EM;
   //int numSizes = face->num_fixed_sizes;
   //cout<<"The units are %d with %d sizes\n",emUnits,numSizes);

   error = FT_Set_Char_Size(face,0,textSize << 6, 96,96);

   if (error)
   {
      cout<<"An error in loading the face\n";
      exit(0);
   }


   const int start = ' ';

   const int end = '~';

   FT_Glyph characters[end - start + 1];

   std::vector<MyVector2> sizes(end - start + 1);

   int area = 0;

   for (int character = start; character <= end; character++)
   {
      int glyph = FT_Get_Char_Index(face, character);

      //cout<<"The piece of %c has an index %d \n",character,glyph);

      error = FT_Load_Glyph(face,glyph, FT_LOAD_RENDER);


      if (error)
      {
         cout<<"An error in loading the face\n";
         exit(0);
      }

      error = FT_Get_Glyph(face->glyph,&characters[character - start]);

      if (error)
      {
         cout<<"An error in loading the face\n";
         exit(0);
      }

      glyphMetric blah;
      blah.width = (double) face->glyph->metrics.width/ (1 << 6);
      blah.height = (double) face->glyph->metrics.height/ (1<<6);

      blah.advance = (double) face->glyph->metrics.horiAdvance/ (1<<6);
      blah.bearingX = (double) face->glyph->metrics.horiBearingX/ (1<<6);
      blah.bearingY = (double) face->glyph->metrics.horiBearingY/ (1<<6);

      charMetrics[character] = blah;

      //cout<<"The size was %d %d\n\n",face->glyph->bitmap.width, face->glyph->bitmap.rows);
      //cout<<"The size was %lf %lf\n\n",blah.width, blah.height);



      MyVector2 theSize = MyVector2(face->glyph->bitmap.width+padding, face->glyph->bitmap.rows+padding);
      sizes[character - start] = theSize;
      area += theSize.x * theSize.y;


   }

   /*
   for (int i = 0 ;i < 26;i++)
   {
      cout<<"the thing %d is %d %d\n",i,sizes[i].x,sizes[i].y);
   }
   */

   side = nexthigher((int) sqrt(area));
   MyVector2 size(side,side);

   bool done = 0;


   AlgoMaxRects algo;
   auto theMap = algo.pack(sizes,size,done);
   cout<<format("\nThe side is %d and %d\n")%side%done;

   if (!done)
   {
      side *= 2;
      size = MyVector2(side,side);
      theMap = algo.pack(sizes,size,done);
      cout<<format("\nThe side is %d and %d\n")%side%done;
   }

   unsigned char *buffer;

   buffer = (unsigned char *)calloc(side * side,1);


   if (!buffer)
   {
      cout<<"No memory\n";
      exit(1);
   }

   for (int ch = start ; ch <= end; ch++)
   {
      MyVector2 theSize = sizes[ch - start];
      FT_BitmapGlyph image = (FT_BitmapGlyph) characters[ch - start];
      auto iter = theMap.find(theSize);

      if (iter == theMap.end())
      {
         cout<<"Not an iter?\n";
         continue;
      }

      MyVector2 theLocation = iter->second;
      theMap.erase(iter);


      charLocations[ch] = MyBox(theLocation.x,side - (theLocation.y + theSize.y -1),theSize.x - 1,(theSize.y -1));

      if (ch == 'A')
      {
         cout<<format("The character %c at %d %d, with size %d %d in a box of size %d \n") % ch % theLocation.x % theLocation.y % theSize.x % theSize.y % side;
         cout<<format("And it has the thing at %d %d %d %d\n") % charLocations[ch].pos.x % charLocations[ch].pos.y % charLocations[ch].size.x % charLocations[ch].size.y;
      }

      for (int y = 0; y< theSize.y-padding; y++)
      {

         for (int x = 0; x < theSize.x-padding; x++)
         {
            buffer[theLocation.x + x + padding/2 + (side -1 - (theLocation.y + y + padding/2)) * side] = image->bitmap.buffer[(y) * (image->bitmap.pitch) + x];


         }

         // cout<<"Writing to %d %d\n",(y + theLocation.y),(theSize.x + theLocation.x));
         //memcpy(buffer + theLocation.x + (side - 1 - (theLocation.y + y)) * side,image->bitmap.buffer + (y) *(image->bitmap.pitch) ,theSize.x);
      }

      FT_Done_Glyph(characters[ch-start]);
   }

   error = FT_Done_FreeType(lib);

   if (error)
   {
      cout<<"There was a problem destroying the freetype library\n";
      exit(0);
   }



   buffer = make_distance_map(buffer, side, side);

   CImg<unsigned char> textOut(buffer,side,side);
   textOut.save_png("/tmp/glutiltext.png");
   filename = "/tmp/glutiltext.png";


   free(buffer);

}

void checkFaceFlags(long faceFlags)
{
   if (faceFlags & FT_FACE_FLAG_SCALABLE)
   {
      cout<<"It is scalable\n";
   }

   if (faceFlags & FT_FACE_FLAG_FIXED_SIZES)
   {
      cout<<"It is fixed sizes\n";
   }

   if (faceFlags & FT_FACE_FLAG_FIXED_WIDTH)
   {
      cout<<"It is fixed width\n";
   }

   if (faceFlags & FT_FACE_FLAG_SFNT)
   {
      cout<<"It is sfnt?\n";
   }

   if (faceFlags & FT_FACE_FLAG_HORIZONTAL)
   {
      cout<<"It is horizontal\n";
   }

   if (faceFlags & FT_FACE_FLAG_VERTICAL)
   {
      cout<<"It is vertical\n";
   }

   if (faceFlags & FT_FACE_FLAG_KERNING)
   {
      cout<<"It is kerning\n";
   }

   if (faceFlags & FT_FACE_FLAG_FAST_GLYPHS)
   {
      cout<<"It is fast glyphs\n";
   }

   if (faceFlags & FT_FACE_FLAG_MULTIPLE_MASTERS)
   {
      cout<<"It is multiple masters\n";
   }

   if (faceFlags & FT_FACE_FLAG_GLYPH_NAMES)
   {
      cout<<"It is glyph names\n";
   }

   if (faceFlags & FT_FACE_FLAG_EXTERNAL_STREAM)
   {
      cout<<"It is external stream\n";
   }

   if (faceFlags & FT_FACE_FLAG_HINTER)
   {
      cout<<"It is hinter\n";
   }

   if (faceFlags & FT_FACE_FLAG_CID_KEYED)
   {
      cout<<"It is cid keyed\n";
   }

   if (faceFlags & FT_FACE_FLAG_TRICKY)
   {
      cout<<"It is tricky\n";
   }
}
