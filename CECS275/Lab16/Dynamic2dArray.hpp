/*
Create a 2D array with user-specified rows and columns.

Insert/Update elements at specific row/column positions.

Retrieve elements at specific row/column positions.

Display the entire 2D array.

Resize the array.

Handle memory safely by properly releasing allocated memory in the destructor.

Implement the class as a template so it works with different data types (int, double, string, etc.).
*/

//#include "Dynamic2dArray.h"
#include <iostream>
#include <iomanip>
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

template<class T>
Dynamic2dArray<T>::Dynamic2dArray(int rowSize, int colSize):rowSize(rowSize), colSize(colSize){
    array = new T* [rowSize];
    for (int i = 0; i < rowSize; i++)
        array[i] = new T[colSize]();

    for(int i = 0; i < rowSize; i++){
        for (int j = 0; j < colSize; j++)
            array[i][j] = T();
    }

}

template<class T>
Dynamic2dArray<T>::~Dynamic2dArray(void){
    for(int i = 0; i < rowSize; i++)
        delete[] array[i];
    delete[] array;
}

template<class T>
void Dynamic2dArray<T>:: resize(int newX, int newY){
    for (int i = 0; i < rowSize; i++)
        delete[] array[i];
    delete[] array;
    
    array = new T * [rowSize];
    for (int i = 0; i < rowSize; i++)
        array[i] = new T[colSize];

}

template<class T>
int Dynamic2dArray<T>::getRowSize(void) const{
    return rowSize;
}

template<class T>
int Dynamic2dArray<T>::getColSize(void) const{
    return colSize;
}

template<class T>
T Dynamic2dArray<T>::getElement(int x, int y) const{
    if (x > rowSize || x < 0 || y > colSize || y < 0)
        throw "Given integers x or y is beyond range\n";
    else
        return array[x][y];
}

template<class T>
void Dynamic2dArray<T>::setRowSize(int newRowSize){
    this -> rowSize = newRowSize;
}

template<class T>
void Dynamic2dArray<T>::setColSize(int newColSize){
    this -> colSize = newColSize;
}

template<class T>
void Dynamic2dArray<T>::insertElement(int x, int y, T value){
    // Ensure proper input validation (e.g., no out-of-bound access)
    try{
        array[x][y] = value;
    } catch(const out_of_range& e){
        cerr << "Value out of range!" << endl;
    }
}

template<class T>
void Dynamic2dArray<T>::draw(void){
    for (int i = 0; i < getRowSize(); i++){
        for (int j = 0; j < getColSize(); j++){
            cout << getElement(i, j) << " ";
        }
        cout << endl;
    }
}