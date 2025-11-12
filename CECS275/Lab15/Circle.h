#ifndef CIRCLE_H
#define CIRCLE_H

#include "Shape.h"
/*
private members: centerX, centerY, radius
public member functions: constructor takes centerX, centerY, radius 
as parameters, getter/setter for private members, 
override calcArea and draw function
*/
class Circle : public Shape {
    private:

    int centerX;
    int centerY;
    int radius;

    public:

    //Constructors
    Circle(int centerX, int centerY, int radius);

    //Getters
    int getCenterX(void) const;
    int getCenterY(void) const;
    int getRadius(void) const;

    //Setters
    void setCenterX(int centerX);
    void setCenterY(int centerY);
    void setRadius(int radius);

    double calcArea(void) const override;
    void draw(char (&Board)[100][100]) override; //not entirely sure how to set up lol 

};
#endif