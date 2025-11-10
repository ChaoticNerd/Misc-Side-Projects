#include "Circle.h"


Circle::Circle(int centerX, int centerY, int radius){
    setCenterX(centerX);
    setCenterY(centerY);
    setRadius(radius);

}

//Getters
int Circle::getCenterX(void) const{
    return centerX;
}

int Circle::getCenterY(void) const{
    return centerY;
}

int Circle::getRadius(void) const{
    return radius;
}

//Setters
void Circle::setCenterX(int centerX){
    this -> centerX = centerX;
}

void Circle::setCenterY(int centerY){
    this -> centerY = centerY;
}

void Circle::setRadius(int radius){
    this -> radius = radius;
}


double Circle::calcArea(void) const{
    return double(getRadius() * getRadius() * 3.14);
}

std::string Circle::draw(void) const{

}
    
