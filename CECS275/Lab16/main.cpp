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
    Dynamic2dArray<string> stringBoard(5,5);
    Dynamic2dArray<string> intBoard(5,5);

    stringBoard.insertElement(8, 8, "asda");
    stringBoard.draw();



}