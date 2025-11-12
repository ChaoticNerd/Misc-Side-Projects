#include "Circle.h"
#include <math.h>

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

void Circle::draw(char (&Board)[100][100]){
    //what do i need to do...
    // x^2 + y ^2 = c^2
    float float_x = 0;
    float float_y = 0;
    float pi = 3.14;
    
    for (int i = 0; i < 360; i++){
        float theta = i * (pi/180);
        float_x = getCenterX() + getRadius() * cos(theta);
        float_y = getCenterY() + getRadius() * sin(theta);
        int x = static_cast<int>(float_x);
        int y = static_cast<int>(float_y);
        
        Board[x][y] = '*';
    }


}
    
