#include "text.h"
#include <cassert>
#include <cmath>
#include "myVector2.h"

#include "algoMaxRects.h"

#include <cstdio>
#include <GL/glew.h>
#include <cstdlib>

#include <ft2build.h>

#include "../util/glUtil.h"
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

void t_textList::addString(const std::string &text,float x, float y)
{
   base.addString(text,x,y,list);
}
void t_textList::draw() const 
{
   base.draw(list);
}
void t_textList::clear()
{
   list.clear();
}


void t_text::draw(const t_renderList &list)
{
   int lastTexture;
   glGetIntegerv(GL_TEXTURE_BINDING_2D,&lastTexture);
   checkGLError();

   glBindTexture(GL_TEXTURE_2D,texture);
   checkGLError();

   list.draw();


   glBindTexture(GL_TEXTURE_2D,lastTexture);
   checkGLError();
}

void t_text::setSize(int _width,int _height)
{
   width = _width;
   height = _height;
}

void t_text::drawString(const std::string &text, float x, float y)
{
   t_textList textList(*this);

   textList.addString(text,x,y);
   textList.draw();
}

void t_text::addString(const std::string &text,float x, float y, t_renderList &list)
{
   for (unsigned int i = 0; i < text.length(); i++)
   {
      char ch = text[i];
      t_myBox box =  charLocations[ch];
      glyphMetric blah = charMetrics[ch];
      //printf("The with was %lf and %lf\n",blah.width,blah.height);

      blah.raster(width,height);

      x+= 100 * blah.bearingX;
      y-= 100 * (blah.height - blah.bearingY);

      list.addRect(x,y,0,(float) box.pos.x/side, (float) box.pos.y/side,
                   x+ 100 * blah.width,y + 100 * blah.height,0, (float)(box.pos.x + box.size.x)/side, (float)(box.pos.y + box.size.y)/side);

      x+= 100 * (blah.advance - blah.bearingX);
      y+= 100 * (blah.height - blah.bearingY);
   }
}


t_text::t_text(int textSize , bool subpixel)
{
   int lastTexture;
   glGetIntegerv(GL_TEXTURE_BINDING_2D,&lastTexture);

   glGenTextures(1,&texture);
   checkGLError();

   glBindTexture(GL_TEXTURE_2D,texture);
   checkGLError();

   FT_Library lib;
   int error = FT_Init_FreeType(&lib);

   if (error)
   {
      printf("An error in loading the library\n");
      exit(0);
   }

   FT_Face face;
   error = FT_New_Face(lib,"../res/DejaVuSans.ttf",0,&face);

   if (error)
   {
      printf("An error in loading the face\n");
      exit(0);
   }


   //long faceFlags = face->face_flags;
   //checkFaceFlags(faceFlags);

   //int emUnits = face->units_per_EM;
   //int numSizes = face->num_fixed_sizes;
   //printf("The units are %d with %d sizes\n",emUnits,numSizes);

   error = FT_Set_Char_Size(face,0,textSize << 6, 96,96);

   if (error)
   {
      printf("An error in loading the face\n");
      exit(0);
   }


   const int start = ' ';

   const int end = '~';

   FT_Glyph characters[end - start + 1];

   std::vector<t_myVector2> sizes(end - start + 1);

   int area = 0;

   for (int character = start; character <= end; character++)
   {
      int glyph = FT_Get_Char_Index(face, character);

      //printf("The piece of %c has an index %d \n",character,glyph);

      if (subpixel)
      {
         error = FT_Load_Glyph(face,glyph, FT_LOAD_RENDER  | FT_LOAD_TARGET_LCD);
      }

      else
      {
         error = FT_Load_Glyph(face,glyph, FT_LOAD_RENDER);
      }


      if (error)
      {
         printf("An error in loading the face\n");
         exit(0);
      }

      error = FT_Get_Glyph(face->glyph,&characters[character - start]);

      if (error)
      {
         printf("An error in loading the face\n");
         exit(0);
      }

      glyphMetric blah;
      blah.width = (double) face->glyph->metrics.width/ (1 << 6);
      blah.height = (double) face->glyph->metrics.height/ (1<<6);

      blah.advance = (double) face->glyph->metrics.horiAdvance/ (1<<6);
      blah.bearingX = (double) face->glyph->metrics.horiBearingX/ (1<<6);
      blah.bearingY = (double) face->glyph->metrics.horiBearingY/ (1<<6);

      charMetrics[character] = blah;

      //printf("The size was %d %d\n\n",face->glyph->bitmap.width, face->glyph->bitmap.rows);
      //printf("The size was %lf %lf\n\n",blah.width, blah.height);

      if (subpixel)
      {
         sizes[character - start] = t_myVector2(face->glyph->bitmap.width/3+1, face->glyph->bitmap.rows+1);
         area += face->glyph->bitmap.width/3 * face->glyph->bitmap.rows;
      }

      else
      {
         sizes[character - start] = t_myVector2(face->glyph->bitmap.width+1, face->glyph->bitmap.rows+1);
         area += face->glyph->bitmap.width * face->glyph->bitmap.rows;
      }


   }

   /*
   for (int i = 0 ;i < 26;i++)
   {
      printf("the thing %d is %d %d\n",i,sizes[i].x,sizes[i].y);
   }
   */

   side = nexthigher((int) sqrt(area));
   t_myVector2 size(side,side);

   bool done = 0;


   t_algoMaxRects algo;
   auto theMap = algo.pack(sizes,size,done);
   printf("\nThe side is %d and %d\n",side,done);

   if (!done)
   {
      side *= 2;
      size = t_myVector2(side,side);
      theMap = algo.pack(sizes,size,done);
      printf("\nThe side is %d and %d\n",side,done);
   }

   char *buffer;

   //buffer = new char[side * side];
   if (subpixel)
   {
      buffer = (char *)calloc(side * side * 4,1);
   }

   else
   {
      buffer = (char *)calloc(side * side,1);
   }


   if (!buffer)
   {
      printf("No memory\n");
      exit(1);
   }

   for (int ch = start ; ch <= end; ch++)
   {
      t_myVector2 theSize = sizes[ch - start];
      FT_BitmapGlyph image = (FT_BitmapGlyph) characters[ch - start];
      auto iter = theMap.find(theSize);

      if (iter == theMap.end())
      {
         printf("Not an iter?\n");
         continue;
      }

      t_myVector2 theLocation = iter->second;
      theMap.erase(iter);


      charLocations[ch] = t_myBox(theLocation.x,side - (theLocation.y + theSize.y -1),theSize.x - 1,(theSize.y -1));

      if (ch == 'A')
      {
         printf("The character %c at %d %d, with size %d %d in a box of size %d \n",ch,theLocation.x,theLocation.y,theSize.x,theSize.y,side);
         printf("And it has the thing at %d %d %d %d\n",charLocations[ch].pos.x,charLocations[ch].pos.y,charLocations[ch].size.x,charLocations[ch].size.y);
      }

      for (int y = 0; y< theSize.y-1; y++)
      {

         for (int x = 0; x < theSize.x-1; x++)
         {
            if (subpixel)
            {
               int r  =  image->bitmap.buffer[(y) * (image->bitmap.pitch) + x*3+0];
               int g  =  image->bitmap.buffer[(y) * (image->bitmap.pitch) + x*3+1];
               int b  =  image->bitmap.buffer[(y) * (image->bitmap.pitch) + x*3+2];
               buffer[theLocation.x*4 + (side -1 - (theLocation.y + y)) * side * 4 +x * 4 + 0] =  r;
               buffer[theLocation.x*4 + (side -1 - (theLocation.y + y)) * side * 4 +x * 4 + 1] =  g;
               buffer[theLocation.x*4 + (side -1 - (theLocation.y + y)) * side * 4 +x * 4 + 2] =  b;
               buffer[theLocation.x*4 + (side -1 - (theLocation.y + y)) * side * 4 +x * 4 + 3] = (r+ g +b)/3 ;
            }

            else
            {
               buffer[theLocation.x + (side -1 - (theLocation.y + y)) * side +x ] =  image->bitmap.buffer[(y) * (image->bitmap.pitch) + x];
            }


         }

         // printf("Writing to %d %d\n",(y + theLocation.y),(theSize.x + theLocation.x));
         //memcpy(buffer + theLocation.x + (side - 1 - (theLocation.y + y)) * side,image->bitmap.buffer + (y) *(image->bitmap.pitch) ,theSize.x);
      }

      FT_Done_Glyph(characters[ch-start]);
   }

   error = FT_Done_FreeType(lib);

   if (error)
   {
      printf("There was a problem destroying the freetype library\n");
      exit(0);
   }


   if (subpixel)
   {
      glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,side,side,0,GL_RGBA,GL_UNSIGNED_BYTE,buffer);
   }

   else
   {
      glTexImage2D(GL_TEXTURE_2D,0,GL_ALPHA,side,side,0,GL_ALPHA,GL_UNSIGNED_BYTE,buffer);
   }

   checkGLError();

   free(buffer);

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   checkGLError();

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   checkGLError();

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
   checkGLError();

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
   checkGLError();

   glBindTexture(GL_TEXTURE_2D,lastTexture);
   checkGLError();

   /*

   for (int y = 0; y < side;y++)
   {
      for (int x = 0; x < side;x++)
      {
         for (int i = 0; i < 3;i++)
         printf("%2d ",(unsigned char)buffer[y * side + x * 4 + i]);

         printf("   ");
      }
      putc('\n',stdout);
   }
   */


}

void checkFaceFlags(long faceFlags)
{
   if (faceFlags & FT_FACE_FLAG_SCALABLE)
   {
      printf("It is scalable\n");
   }

   if (faceFlags & FT_FACE_FLAG_FIXED_SIZES)
   {
      printf("It is fixed sizes\n");
   }

   if (faceFlags & FT_FACE_FLAG_FIXED_WIDTH)
   {
      printf("It is fixed width\n");
   }

   if (faceFlags & FT_FACE_FLAG_SFNT)
   {
      printf("It is sfnt?\n");
   }

   if (faceFlags & FT_FACE_FLAG_HORIZONTAL)
   {
      printf("It is horizontal\n");
   }

   if (faceFlags & FT_FACE_FLAG_VERTICAL)
   {
      printf("It is vertical\n");
   }

   if (faceFlags & FT_FACE_FLAG_KERNING)
   {
      printf("It is kerning\n");
   }

   if (faceFlags & FT_FACE_FLAG_FAST_GLYPHS)
   {
      printf("It is fast glyphs\n");
   }

   if (faceFlags & FT_FACE_FLAG_MULTIPLE_MASTERS)
   {
      printf("It is multiple masters\n");
   }

   if (faceFlags & FT_FACE_FLAG_GLYPH_NAMES)
   {
      printf("It is glyph names\n");
   }

   if (faceFlags & FT_FACE_FLAG_EXTERNAL_STREAM)
   {
      printf("It is external stream\n");
   }

   if (faceFlags & FT_FACE_FLAG_HINTER)
   {
      printf("It is hinter\n");
   }

   if (faceFlags & FT_FACE_FLAG_CID_KEYED)
   {
      printf("It is cid keyed\n");
   }

   if (faceFlags & FT_FACE_FLAG_TRICKY)
   {
      printf("It is tricky\n");
   }
}
