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
void Rectangle::draw(char (&board)[100][100]){
    int topLeftX = getCenterX() - (getWidth() / 2);
    int topLeftY = getCenterY() - (getHeight() / 2);

    // print first row, forward
    for(int i = topLeftX; i < (topLeftX + getWidth()); i++){
        board[topLeftX][i] = '*';
    }
    
    // print columns
    for(int i = topLeftX; i < getHeight() + topLeftX; i++){
        board[i][topLeftY-1] = '*';
        board[i][topLeftY + static_cast<int>(getWidth())-1] = '*';
    }

    // paint last row horizontal
    for(int i = topLeftX; i < (topLeftX + getWidth()); i++){
        board[topLeftX + static_cast<int>(getHeight()) - 1][i] = '*';
    }
}