#include <iostream>
#include "Circle.h"
using namespace std;
/*
 *  After you implement all the classes above, write a main function 
 *  Create an array of Shape and add different Circle and Rectangle with different sizes into this array.
*/
int main(void){
    Circle round(50,50,10);
    char board[100][100];

    
    for (int i = 0; i < 100; ++i) {
        for (int j = 0; j < 100; ++j) {
            board[i][j] = '.';
        }
    }
    round.draw(board);

    // print board
    for(int i = 0; i < 100; i++){
        for(int j = 0; j < 100; j++){
            cout << board[i][j];
        }
        cout << endl;
    }
}