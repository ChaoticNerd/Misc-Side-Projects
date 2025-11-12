#include "Rectangle.h"
#include <iostream>
#include "Circle.h"
using namespace std;
/*
 *  After you implement all the classes above, write a main function 
 *  Create an array of Shape and add different Circle and Rectangle with different sizes into this array.
*/
int main(void){
    Rectangle notQuiteSquare(10,10,20,20);
    Circle round(20,20,10);

    char board[100][100];    

    cout << "====== Rectangle ====== " << endl;
    cout << "Width: " << notQuiteSquare.getWidth() << endl;
    cout << "Height: " << notQuiteSquare.getHeight() << endl;
    cout << "Center X: " << notQuiteSquare.getCenterX() << endl;
    cout << "Center Y: " << notQuiteSquare.getCenterY() << endl;
    cout << "Area of rectangle: " << notQuiteSquare.calcArea() << endl;

    cout << "Setting width to 5: " << endl;
    notQuiteSquare.setWidth(5);
    cout << "Width: " << notQuiteSquare.getWidth() << endl;

    cout << "Setting height to 92: " << endl;
    notQuiteSquare.setHeight(92);
    cout << "Height: " << notQuiteSquare.getHeight() << endl;
    
    cout << "Setting Center X to 70: " << endl;
    notQuiteSquare.setCenterX(70);
    cout << "Center X: " << notQuiteSquare.getCenterX() << endl;

    cout << "Setting Center Y to 2: " << endl;
    notQuiteSquare.setCenterY(2);
    cout << "Center Y: " << notQuiteSquare.getCenterY() << endl;
    cout << "Area of rectangle: " << notQuiteSquare.calcArea() << endl;

    cout << "Setting values back" << endl;
    notQuiteSquare.setWidth(10);
    notQuiteSquare.setHeight(10);
    notQuiteSquare.setCenterX(20);;
    notQuiteSquare.setCenterY(20);

    cout << "====== Circle ====== " << endl;
    cout << "Radius: " << round.getRadius() << endl;
    cout << "Center X: " << round.getCenterX() << endl;
    cout << "Center Y: " << round.getCenterY() << endl;
    cout << "Area of Cricle: " << round.calcArea() << endl;

    cout << "Setting Radius to 5: " << endl;
    round.setRadius(5);
    cout << "Radius: " << round.getRadius() << endl;
    
    cout << "Setting Center X to 70: " << endl;
    round.setCenterX(70);
    cout << "Center X: " << round.getCenterX() << endl;

    cout << "Setting Center Y to 2: " << endl;
    round.setCenterY(2);
    cout << "Center Y: " << round.getCenterY() << endl;
    cout << "Area of Circle: " << round.calcArea() << endl;

    cout << "Setting values back" << endl;
    round.setRadius(10);
    round.setCenterX(20);;
    round.setCenterY(20);

    
    for (int i = 0; i < 100; ++i) {
        for (int j = 0; j < 100; ++j) {
            board[i][j] = '.';
        }
    }

    notQuiteSquare.draw(board);
    round.draw(board);
    
    // print board
    for(int i = 0; i < 100; i++){
        for(int j = 0; j < 100; j++){
            cout << board[i][j];
        }
        cout << endl;
    }
    
    return 0;

}