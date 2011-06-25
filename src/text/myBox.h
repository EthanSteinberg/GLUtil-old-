/*
-------------------------------------------------------------------------
This file is part of PixelPacker, tools to pack textures into as small as space as possible.

PixelPacker version 1 of 6 March 2011
Copyright (C) 2011 Ethan Steinberg <ethan.steinberg@gmail.com>

This program is released under the terms of the license contained
in the file COPYING.
---------------------------------------------------------------------------
*/


#ifndef MY_BOX_H_INCLUDED
#define MY_BOX_H_INCLUDED

#include "myVector2.h"

class MyBox
{
public:
   MyBox();
   MyBox(int x, int y, int width, int height);
   MyBox(MyVector2 pos,MyVector2 size);

   bool operator==(const MyBox &box) const;
   bool operator<(const MyBox &box) const;

   MyVector2 pos;
   MyVector2 size;
};


#endif
