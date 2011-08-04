/*
-------------------------------------------------------------------------
This file is part of PixelPacker, tools to pack textures into as small as space as possible.

PixelPacker version 1 of 6 March 2011
Copyright (C) 2011 Ethan Steinberg <ethan.steinberg@gmail.com>

This program is released under the terms of the license contained
in the file COPYING.
---------------------------------------------------------------------------
*/


#include "algoMaxRects.h"
#include <iostream>
#include <stdexcept>
#include <vector>
#include <set>
#include <boost/foreach.hpp>
#include <list>
#include <algorithm>

#include <assert.h>

std::multimap<MyVector2, MyVector2> AlgoMaxRects::pack(const std::vector< MyVector2> &temp, const MyVector2 &size, bool &fine)
{
   std::list<MyBox> freeBoxes;
   freeBoxes.push_back(MyBox(0,0,size.x,size.y));

   std::list<MyVector2> rects(temp.begin(), temp.end());

   std::multimap<MyVector2, MyVector2> boxes;

   while (!rects.empty())
   {
      int min = std::max(size.x,size.y);

      std::list<MyVector2>::iterator minIterRects = rects.end();
      std::list<MyBox>::iterator minIterFreeBoxes = freeBoxes.end();

      for (auto iterRects = rects.begin(); iterRects != rects.end(); iterRects++)
      {
         for (auto iterFreeBoxes = freeBoxes.begin(); iterFreeBoxes != freeBoxes.end(); iterFreeBoxes++)
         {

            int distance = std::min(iterFreeBoxes->size.y - iterRects->y, iterFreeBoxes->size.x - iterRects->x);

            if (distance < 0)
            {
               //std::cout<<"The box "<<iterFreeBoxes->pos<<" with a size "<<iterFreeBoxes->size<<" is too small for "<<*iterRects<<std::endl;
               continue;
            }

            if (distance < min)
            {
               //std::cout<<"The box "<<iterFreeBoxes->pos<<" with a size "<<iterFreeBoxes->size<<" is ok for "<<*iterRects<<std::endl;
               min = distance;
               minIterRects = iterRects;
               minIterFreeBoxes = iterFreeBoxes;
            }

         }
      }

      if (minIterRects == rects.end() || minIterFreeBoxes == freeBoxes.end())
      {
         return std::multimap<MyVector2, MyVector2>();
      }
      

      //std::cout<<"I am placing the box "<<*minIterRects<<" into the position "<<minIterFreeBoxes->pos<<std::endl;
      //std::cout<<minIterFreeBoxes->pos<<std::endl;

      MyBox insertedBox = MyBox(minIterFreeBoxes->pos,*minIterRects);
      boxes.insert(std::make_pair(*minIterRects,minIterFreeBoxes->pos));

      freeBoxes.push_front(MyBox(
                             MyVector2(
                                minIterFreeBoxes->pos.x + minIterRects->x,
                                minIterFreeBoxes->pos.y + 0),

                             MyVector2(
                                minIterFreeBoxes->size.x - minIterRects->x,
                                minIterFreeBoxes->size.y)
                          ));


      freeBoxes.push_front(MyBox(
                             MyVector2(
                                minIterFreeBoxes->pos.x + 0,
                                minIterFreeBoxes->pos.y + minIterRects->y),

                             MyVector2(
                                minIterFreeBoxes->size.x,
                                minIterFreeBoxes->size.y - minIterRects->y)
                          ));


      freeBoxes.erase(minIterFreeBoxes);


      MyVector2 a1 = insertedBox.pos;
      //MyVector2 a2 = MyVector2(insertedBox.pos.x + insertedBox.size.x,insertedBox.pos.y);
      MyVector2 a3 = MyVector2(insertedBox.pos.x + insertedBox.size.x,insertedBox.pos.y + insertedBox.size.y);
      //MyVector2 a4 = MyVector2(insertedBox.pos.x                     ,insertedBox.pos.y + insertedBox.size.y);

      for (auto iterFreeBoxes = freeBoxes.begin(); iterFreeBoxes != freeBoxes.end();)
      {
         assert(iterFreeBoxes != freeBoxes.end());
         //assert(!(iterFreeBoxes->pos == insertedBox.pos));
         MyVector2 b1 = iterFreeBoxes->pos;
         //MyVector2 b2 = MyVector2(iterFreeBoxes->pos.x + iterFreeBoxes->size.x,iterFreeBoxes->pos.y);
         MyVector2 b3 = MyVector2(iterFreeBoxes->pos.x + iterFreeBoxes->size.x,iterFreeBoxes->pos.y + iterFreeBoxes->size.y);
         //MyVector2 b4 = MyVector2(iterFreeBoxes->pos.x                        ,iterFreeBoxes->pos.y + iterFreeBoxes->size.y);

         if ((a1.x >= b3.x) || (a1.y >= b3.y) ||
               (a3.x <= b1.x) || (a3.y <= b1.y))
         {
            iterFreeBoxes++;
            continue;   // not intersecting
         }


         if ((a1.x > b1.x) /*  && (a1.x < b3.x) */) // If there is a chance that line a1,a2 is in the shape b
         {
            freeBoxes.push_front(MyBox(
                                    MyVector2(
                                       iterFreeBoxes->pos.x,
                                       iterFreeBoxes->pos.y),

                                    MyVector2(
                                       a1.x - b1.x,
                                       iterFreeBoxes->size.y)
                                 ));
         }

         if ((a3.x < b3.x) /*  && (a1.x < b3.x) */) // If there is a chance that line a1,a2 is in the shape b
         {
            freeBoxes.push_front(MyBox(
                                    MyVector2(
                                       a3.x,
                                       iterFreeBoxes->pos.y),

                                    MyVector2(
                                       b3.x - a3.x,
                                       iterFreeBoxes->size.y)
                                 ));
         }

         if ((a1.y > b1.y) /*  && (a1.x < b3.x) */) // If there is a chance that line a1,a2 is in the shape b
         {
            freeBoxes.push_front(MyBox(
                                    MyVector2(
                                       iterFreeBoxes->pos.x,
                                       iterFreeBoxes->pos.y),

                                    MyVector2(
                                       iterFreeBoxes->size.x,
                                       a1.y - b1.y)
                                 ));
         }

         if ((a3.y < b3.y) /*  && (a1.x < b3.x) */) // If there is a chance that line a1,a2 is in the shape b
         {
            freeBoxes.push_front(MyBox(
                                    MyVector2(
                                       iterFreeBoxes->pos.x,
                                       a3.y),

                                    MyVector2(
                                       iterFreeBoxes->size.x,
                                       b3.y - a3.y)
                                 ));
         }

         auto blah = iterFreeBoxes++;
         freeBoxes.erase(blah);

      }

      for (auto iterFreeBoxes = freeBoxes.begin(); iterFreeBoxes != freeBoxes.end(); iterFreeBoxes++)
      {
         assert(iterFreeBoxes != freeBoxes.end());
         auto iterFreeBoxes2 = iterFreeBoxes;
         iterFreeBoxes2++;

         while ( iterFreeBoxes2 != freeBoxes.end())
         {
            assert(iterFreeBoxes != freeBoxes.end());

            assert(iterFreeBoxes2 != freeBoxes.end());
            assert(iterFreeBoxes != iterFreeBoxes2);
            //assert(!((*iterFreeBoxes).pos == (*iterFreeBoxes2).pos));

            MyVector2 b1 = iterFreeBoxes->pos;
            //MyVector2 b2 = MyVector2(iterFreeBoxes->pos.x + iterFreeBoxes->size.x,iterFreeBoxes->pos.y);
            MyVector2 b3 = MyVector2(iterFreeBoxes->pos.x + iterFreeBoxes->size.x,iterFreeBoxes->pos.y + iterFreeBoxes->size.y);
            //MyVector2 b4 = MyVector2(iterFreeBoxes->pos.x                        ,iterFreeBoxes->pos.y + iterFreeBoxes->size.y);

            MyVector2 c1 = iterFreeBoxes2->pos;
            //MyVector2 c2 = MyVector2(iterFreeBoxes2->pos.x + iterFreeBoxes2->size.x,iterFreeBoxes2->pos.y);
            MyVector2 c3 = MyVector2(iterFreeBoxes2->pos.x + iterFreeBoxes2->size.x,iterFreeBoxes2->pos.y + iterFreeBoxes2->size.y);
            //MyVector2 c4 = MyVector2(iterFreeBoxes2->pos.x                         ,iterFreeBoxes2->pos.y + iterFreeBoxes2->size.y);

            if (c1.x >= b1.x && c1.y >= b1.y &&
                  c3.x <= b3.x && c3.y <= b3.y)
            {
               //std::cout<<"Erasing a box "<<iterFreeBoxes->pos<<", "<<iterFreeBoxes->size<<" and "<<iterFreeBoxes2->pos<<", "<<iterFreeBoxes2->size<<std::endl;
               auto blah = iterFreeBoxes2++;
               freeBoxes.erase(blah);
            }

            else 
               iterFreeBoxes2++;

         }
      }


      /*
      BOOSFOREACH(MyBox &lol, freeBoxes)
      {
         //std::cout<<"A free box with "<<lol.pos<<std::endl;
      }
      */

      rects.erase(minIterRects);
      //std::cout<<"Finished with said loop"<<std::endl;


   }

   fine = 1;
   return boxes;
}

