/*
-------------------------------------------------------------------------
This file is part of PixelPacker, tools to pack textures into as small as space as possible.

PixelPacker version 1 of 6 March 2011
Copyright (C) 2011 Ethan Steinberg <ethan.steinberg@gmail.com>

This program is released under the terms of the license contained
in the file COPYING.
---------------------------------------------------------------------------
*/


#include "myVector2.h"
#include <utility>

using namespace std::rel_ops;

MyVector2::MyVector2()
{}

MyVector2::MyVector2(int X, int Y)
{
   x = X;
   y = Y;
}

std::ostream &operator<<(std::ostream &out, const MyVector2 &vec2)
{
   out<<"X: "<<vec2.x<<" Y:"<<vec2.y;
   return out;
}

bool MyVector2::operator==(const MyVector2 &vec) const
{
   return (vec.x == x) && (vec.y == y);
}

bool MyVector2::operator<(const MyVector2 &vec) const
{
   if (vec.x < x)
      return 1;

   else if (vec.x > x)
      return 0;

   else if (vec.y < y)
      return 1;

   else 
      return 0;
}
