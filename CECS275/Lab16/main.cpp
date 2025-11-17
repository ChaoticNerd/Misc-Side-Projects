#include "Dynamic2dArray.hpp"
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

/*
Provide a tester program (main.cpp) where you:

    Create a Dynamic2DArray<int> and store integer values.

    Create a Dynamic2DArray<string> and store strings (e.g., names).

    Demonstrate insertion, retrieval, and display functions.

*/

int main(void){
    cout << "Create string board" << endl;
    Dynamic2dArray<string> stringBoard(5,5);
    cout << endl;

    cout << "Create int board" << endl;
    Dynamic2dArray<int> intBoard(5,5);

    cout << "====================================================" << endl << endl;    
    cout << "Populating string and int boards using insert Element" << endl;
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            stringBoard.insertElement(i, j, to_string(i+1));
            intBoard.insertElement(i,j,i+1);
        }
    }
    cout << "Both boards populated" << endl << endl;
    cout << "====================================================" << endl;
    cout << "Drawing out string board" << endl;
    stringBoard.draw();
    cout << endl;

    cout << "Drawing out integer board" << endl;
    intBoard.draw();
    cout << endl;

    /*
        Left to demonstrate:
        int getRowSize(void) const;
        int getColSize(void) const;
        T getElement(int, int)const; 
        void setRowSize(int);
        void setColSize(int);
        void resize(int, int);
    */
}