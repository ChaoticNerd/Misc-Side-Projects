#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Shape.h"

/*
Derived class from Shape called Rectangle:
private members: width, height, centerX, centerY
public member functions: constructor takes width, height, centerX, and centerY as parameters, getter/setter for private members, override calcArea and draw function
*/
class Rectangle : public Shape{
    private:
        double width;
        double height;
        int centerX;
        int centerY;
    
    public:
        Rectangle(double width, double height, int centerX, int centerY);

        // Getters
        double  getWidth(void)      const;
        double  getHeight(void)     const;
        int     getCenterX(void)    const;
        int     getCenterY(void)    const;

        // Setters
        void    setWidth(double);
        void    setHeight(double);
        void    setCenterX(int);
        void    setCenterY(int);

        double calcArea(void) const override;
        void draw(char (&board)[100][100])override;

};
#endif