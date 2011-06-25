/*
-------------------------------------------------------------------------
This file is part of PixelPacker, tools to pack textures into as small as space as possible.

PixelPacker version 1 of 6 March 2011
Copyright (C) 2011 Ethan Steinberg <ethan.steinberg@gmail.com>

This program is released under the terms of the license contained
in the file COPYING.
---------------------------------------------------------------------------
*/


#ifndef MY_VECTOR_2_H_INCLUDED
#define MY_VECTOR_2_H_INCLUDED

#include <ostream>

class MyVector2
{
public:
   MyVector2();
   MyVector2(int x, int y);

   friend std::ostream& operator<<(std::ostream &out, const MyVector2 &vec2);

   bool operator==(const MyVector2 &vec) const;
   bool operator<(const MyVector2 &vec) const;

   int x;
   int y;
};


#endif
