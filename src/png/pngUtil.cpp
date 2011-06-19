#include <GL/glew.h>
#include <png.h>
#include "util.h"
#include "glUtil.h"
#include <vector>

void loadTexture(const std::string &filename)
{
   FILE *theFile = fopen(filename.c_str(),"rb");

   if (!theFile)
   {
      perror("Fopen failed");
      exit(1);
   }

   char header[8];
   fread(header,1,8,theFile);

   if (ferror(theFile))
   {
      perror("Fread failed");
      exit(1);
   }

   if (png_sig_cmp((png_byte *) header,0,8))
   {
      printf("The file is not a png\n");
      exit(1);
   }

   png_structp png_ptr = png_create_read_struct(
                            PNG_LIBPNG_VER_STRING,
                            NULL,NULL,NULL
                         );

   if (!png_ptr)
   {
      printf("Failed initialization of png_ptr\n");
      exit(1);
   }

   png_infop info_ptr = png_create_info_struct(png_ptr);

   if (!info_ptr)
   {
      png_destroy_read_struct(&png_ptr,
                              (png_infopp)NULL, (png_infopp)NULL);
      printf("Info ptr creation failed\n");
      exit(1);
   }

   png_infop end_info = png_create_info_struct(png_ptr);

   if (!end_info)
   {
      png_destroy_read_struct(&png_ptr, &info_ptr,
                              (png_infopp)NULL);
      printf("Info ptr creation failed\n");
      exit(1);
   }

   png_init_io(png_ptr,theFile);
   png_set_sig_bytes(png_ptr,8);

   png_read_info(png_ptr,info_ptr);
   int width = png_get_image_width(png_ptr,info_ptr);
   int height = png_get_image_height(png_ptr,info_ptr);
   int depth = png_get_bit_depth(png_ptr,info_ptr);
   int rowbytes = png_get_rowbytes(png_ptr, info_ptr);
   int colorType = png_get_color_type(png_ptr,info_ptr);

   std::vector<png_byte> image_data(rowbytes * height);

   std::vector<png_bytep> row_pointers(height);
   for (int i = 0; i < height; ++i)
           row_pointers[i] = &image_data[0] + i * rowbytes;


   printf("I have read the image with width %d, height %d, depth %d, rowbytes %d\n",width,height,depth,rowbytes);

   png_read_image(png_ptr,&row_pointers[0]);

   png_read_end(png_ptr,NULL);
   png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);

   
   if (colorType == PNG_COLOR_TYPE_RGB)
   glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,&image_data[0]);
   else //(colorType == PNG_COLOR_TYPE_RGBA)
   glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width,height,0,GL_RGBA,GL_UNSIGNED_BYTE,&image_data[0]);
   checkGLError();

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   checkGLError();

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   checkGLError();

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
   checkGLError();

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
   checkGLError();
   
}
