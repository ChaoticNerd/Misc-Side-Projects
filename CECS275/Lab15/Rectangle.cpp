#include "Rectangle.h"

Rectangle::Rectangle(double width, double height, int centerX, int centerY){
    setWidth(width);
    setHeight(height);
    setCenterX(centerX);
    setCenterY(centerY);
}

// Setters

void Rectangle::setWidth(double width){
    this -> width = width;
}

void Rectangle::setHeight(double height){
    this -> height = height;
}

void Rectangle::setCenterX(int centerX){
    this -> centerX = centerX;
}

void Rectangle::setCenterY(int centerY){
    this -> centerY = centerY;
}


// Getters

double Rectangle::getWidth(void) const{
    return width;
}

double Rectangle::getHeight(void) const{
    return height;
}

int Rectangle::getCenterX(void) const{
    return centerX;
}

int Rectangle::getCenterY(void) const{
    return centerY;
}

// Overriding functions from Shape class

double Rectangle::calcArea(void) const{
    return getWidth() * getHeight();
}

// Not sure this is right? Does he want us to place an R or something in a 2D array or to draw it?
std::string Rectangle::draw(void) const{
    std::string rectFat(getWidth() - 2, ' ');
    std::string rect = "";
    
    for(int i = 0; i < static_cast<int>(getWidth()); i++)
        rect += "-";
    
    rect += "\n";

    for(int i = 0; i < static_cast<int>(getHeight()); i++){
        rect += "|";
        rect += rectFat;
        rect += "|\n";
    }

    for(int i = 0; i < static_cast<int>(getWidth()); i++)
        rect += "-";

    return rect;
}