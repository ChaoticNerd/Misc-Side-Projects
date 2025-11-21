/*
Create a 2D array with user-specified rows and columns.

Insert/Update elements at specific row/column positions.

Retrieve elements at specific row/column positions.

Display the entire 2D array.

Resize the array.

Handle memory safely by properly releasing allocated memory in the destructor.

Implement the class as a template so it works with different data types (int, double, string, etc.).
*/
#include <iostream>
#include <stdexcept>
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
    this -> setColSize(newY);
    this -> setRowSize(newX);
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
    try{
        if ( x < 0 || x >= rowSize)
            throw out_of_range("X is out of bounds");
        else if ( y < 0 || y >= colSize)
            throw out_of_range("Y is out of bounds");
        else 
            return array[x][y];
        //checking X or Y
    }catch (out_of_range &ex){
        cerr << "Caught Out of Bounds: " << ex.what() << endl;
        return array[0][0];
    }catch(...){
        cout << "catching something else(lochness)" <<endl;
        return array[0][0];
    }
    
}

template<class T>
void Dynamic2dArray<T>::setRowSize(int newRowSize){
    for(int i = 0; i < rowSize; i++){
        delete[] array[i];
    }
    delete[] array;

    this -> rowSize = newRowSize;

    array = new T* [rowSize];
    for (int i = 0; i < rowSize; i++)
        array[i] = new T[colSize]();

    for(int i = 0; i < rowSize; i++){
        for (int j = 0; j < colSize; j++)
            array[i][j] = T();
    }

}

template<class T>
void Dynamic2dArray<T>::setColSize(int newColSize){
    for(int i = 0; i < rowSize; i++){
        delete[] array[i];
    }
    delete[] array;

    this -> colSize = newColSize;

    array = new T* [rowSize];
    for (int i = 0; i < rowSize; i++)
        array[i] = new T[colSize]();

    for(int i = 0; i < rowSize; i++){
        for (int j = 0; j < colSize; j++)
            array[i][j] = T();
    }
}

template<class T>
void Dynamic2dArray<T>::insertElement(int x, int y, T value){
    try{
        if ( x < 0 || x >= rowSize)
            throw out_of_range("X is out of bounds");
        if ( y < 0 || y >= rowSize)
            throw out_of_range("Y is out of bounds");
        else 
            this -> array[x][y] = value;
        //checking X or Y
    }catch (out_of_range &ex){
        cerr << "Caught Out of Bounds: " << ex.what() << endl;
    }catch(...){
        cout << "catching something else(lochness)" <<endl;
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