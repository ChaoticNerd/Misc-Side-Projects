#ifndef SHAPE_H
#define SHAPE_H

#include <string>

/*
    Pure abstract base class called Shape:
    public member functions: calcArea (virtual function), and draw()
*/
class Shape{
    public:
        //virtual ~Shape() = default;                    
        virtual double calcArea(void) const = 0;       // Returns calculated area
        virtual void draw(char (&board)[100][100]) = 0;          // Use a 2D array to act as a coordinate system. Do not use any graphics library.
};
#endif