#include <iostream>
#include <iomanip>
#include <string>
#include "Dynamic2dArray.h"
using namespace std;

int main(void){
    Dynamic2dArray<string> Board(5,5);
    Board.insertElement(3, 3, "asda");//feq
    Board.draw();



}