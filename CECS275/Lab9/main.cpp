#include "fontLibrary.h"
#include "processInput.h"

int main(void){

    string userInput = getUserInput();

    // holding space for null char
    char* userInputChars = new char[userInput.length() + 1];

    processUserInput(userInput, userInputChars); // this function call breaks :: char* is a nullptr

    /*///////////////////////////////// debug/testing //////////////////////////////////
    cout << "*userInputChars produces: "    << *userInputChars      << endl; // this prints h (first char)
    cout << "userInputChars produces "      << userInputChars       << endl; // this prints whatever is in userInput
    cout << "userInputChars[3] produces "   << userInputChars[3]    << endl; // this prints whatever is in third index of userInput
    //////////////////////////////////////////////////////////////////////////////////*/

    return 0;
}
