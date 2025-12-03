#include "Dynamic2dArray.hpp"
#include <iostream>
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
            stringBoard.insertElement(i, j, "B");
            intBoard.insertElement(i,j,i+1);
        }
    }
    stringBoard.insertElement(2, 3, "P");

    cout << "Both boards populated" << endl << endl;
    cout << "====================================================" << endl << endl;
    cout << "Drawing out string board" << endl;
    stringBoard.draw();
    cout << endl;

    cout << "Drawing out integer board" << endl;
    intBoard.draw();
    cout << endl;

    cout << "Over Indexing String Board  with getElement()" << endl;

    cout << stringBoard.getElement(6,0) << endl;
    cout << "I dont crash yet1" << endl;
    cout << stringBoard.getElement(1,-2) << endl;
    cout << "I dont crash yet2" << endl;
    
    cout << "Over Indexing String Board with insertElement()" << endl;
    intBoard.draw();
    intBoard.insertElement(3,12,1);
    cout << "I dont crash yet1" << endl;
    intBoard.insertElement(-2,1,1);
    cout << "I dont crash yet2" << endl;
    intBoard.draw();


    /*
        Left to demonstrate:
        int getRowSize(void) const;
        int getColSize(void) const;
        void setRowSize(int);
        void setColSize(int);
        void resize(int, int);
    */
    cout << "====================================================" << endl << endl;

    cout << "Current stringBoard row size: " << stringBoard.getRowSize() << endl; 
    cout << "Current stringBoard col size: " << stringBoard.getColSize() << endl << endl; 

    cout << "Change stringBoard row size to 200." << endl;
    stringBoard.setRowSize(200);
    cout << "Change stringBoard col size to 8." << endl << endl;
    stringBoard.setColSize(8);

    cout << "Changed stringBoard row size: " << stringBoard.getRowSize() << endl; 
    cout << "Changed stringBoard col size: " << stringBoard.getColSize() << endl << endl; 

    cout << "Populating stringBoard using insert Element" << endl;
    for(int i = 0; i < stringBoard.getRowSize(); i++){
        for(int j = 0; j < stringBoard.getColSize(); j++){
            stringBoard.insertElement(i, j, to_string(i+1));
        }
    }
    cout << "Draw the changed size: " << endl;
    stringBoard.draw();

    cout << "====================================================" << endl;

    cout << "Resizing stringBaord to x = 5 and y = 5." << endl;
    stringBoard.resize(5, 5);

    cout << "Changed stringBoard row size: " << stringBoard.getRowSize() << endl; 
    cout << "Changed stringBoard col size: " << stringBoard.getColSize() << endl << endl; 

    cout << "Populating stringBoard using insert Element" << endl;
    for(int i = 0; i < stringBoard.getRowSize(); i++){
        for(int j = 0; j < stringBoard.getColSize(); j++){
            stringBoard.insertElement(i, j, to_string(i+1));
        }
    }

    cout << "Draw the changed size: " << endl;
    stringBoard.draw();

    cout << "Getting whatever is in stringBoard[0,4]: " << stringBoard.getElement(0, 4) << endl << endl;

    cout << "====================================================" << endl << endl;

    cout << "Current intBoard row size: " << intBoard.getRowSize() << endl; 
    cout << "Current intBoard col size: " << intBoard.getColSize() << endl << endl; 

    cout << "Change intBoard row size to 200." << endl;
    intBoard.setRowSize(200);
    cout << "Change intBoard col size to 8." << endl << endl;
    intBoard.setRowSize(8);

    cout << "Changed intBoard row size: " << intBoard.getRowSize() << endl; 
    cout << "Changed intBoard col size: " << intBoard.getColSize() << endl << endl; 

    cout << "Populating intBoard using insert Element" << endl;
    for(int i = 0; i < intBoard.getRowSize(); i++){
        for(int j = 0; j < intBoard.getColSize(); j++){
            intBoard.insertElement(i, j, i+1);
        }
    }

    cout << "Draw the changed size: " << endl;
    intBoard.draw();

    cout << "====================================================" << endl;

    cout << "Resizing intBoard to x = 5 and y = 5." << endl;
    intBoard.resize(5, 5);

    cout << "Changed intBoard row size: " << intBoard.getRowSize() << endl; 
    cout << "Changed intBoard col size: " << intBoard.getColSize() << endl << endl; 

    cout << "Populating intBoard using insert Element" << endl;
    for(int i = 0; i < intBoard.getRowSize(); i++){
        for(int j = 0; j < intBoard.getColSize(); j++){
            intBoard.insertElement(i, j, i+1);
        }
    }
    
    cout << "Draw the changed size: " << endl;
    intBoard.draw();

    cout << "Getting whatever is in intBoard[3,2]: " << intBoard.getElement(3, 2) << endl;

    Dynamic2dArray<double> doubleBoard(5,5);
    for(int i = 0; i < doubleBoard.getRowSize(); i++){
        for(int j = 0; j < doubleBoard.getColSize(); j++){
            doubleBoard.insertElement(i, j, i+1);
        }
    }
    doubleBoard.insertElement(3,3,200.6);
    doubleBoard.draw();
}