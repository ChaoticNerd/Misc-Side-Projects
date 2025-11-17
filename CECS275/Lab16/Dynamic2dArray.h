/*
Create a 2D array with user-specified rows and columns.
 X 
Insert/Update elements at specific row/column positions.
 - setElement X
 - setRowSize X
 - setColSize X

Retrieve elements at specific row/column positions.
 - getElement X
 - getRowSize X
 - getColSize X
 - getRows ? 
 - getCols ?  

Display the entire 2D array.
- drawArray X

Resize the array.
- resize() X

Handle memory safely by properly releasing allocated memory in the destructor.

Implement the class as a template so it works with different data types (int, double, string, etc.).
*/
#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

#include <iostream>
#include <vector>
using namespace std;


template<class T>
class Dynamic2dArray{
    private:
        int rowSize;    
        int colSize;
        T** array;

    public:    
    //constructor
        Dynamic2dArray(int rowSize, int colSize);

    //Decstructor
        ~Dynamic2dArray();

    //getters
        int getRowSize(void) const;
        int getColSize(void) const;
        T getElement(int, int)const; 


    //setters
        void setRowSize(int);
        void setColSize(int);
        void insertElement(int, int, T);
    
    //Resize
        void resize(int, int);

        void draw(void);



};

#endif