#include "fontLibrary.h"
#include "processInput.h"
#include <memory>
#include <iostream>

void cleaningGnome(unique_ptr<char[]> &userInputChars, string** binString);

int main(void){

    string userInput = getUserWord();
    int userInputSize = userInput.length(); // rows
    //int isBolded = isBold();
    int isBolded = 8; // columns
    
    string** binString;
    binString = new string*[userInputSize]; // this is the rows
    for (int i = 0; i < userInputSize; ++i) {
        binString[i] = new string[isBolded];
        for(int j = 0; j < isBolded; j++){ // this runs 0 to 7
            binString[i][j] = "N";
        cout << " CHECKING BINSTRING at i: " << i << " and j: " << j << " " << binString[i][j] << endl;

        }
        // cout << binString[i] << " CHECKING BINSTRING i" << endl;
    }


    
    // // holding space for null char
    unique_ptr<char[]> userInputChars( new char[userInputSize + 1]);
    // cout << "FUCK MY STUPID BAKA LIFE" << endl;

    processUserInput(userInput, userInputChars); 

    // // cout << "\u001b[8;42m   00011101010  \u001b[0m" << endl;
    // // cout << ESCAPE_CHARACTER << HIDE << ';' << GREEN_BACKGROUND  << " ASDJKHASKJDAS " << ESCAPE_CHARACTER <<"0m" << endl;
    cout << "IM NOT FINE"<< endl;
    user2Bin(userInputChars, userInputSize, binString);
    cout << "IM FINE"<< endl;


    showPixels(binString, isBolded, userInputSize);
    cout << "HOT MILFS IN YOUR AREA " << endl;

    ///////////////////////////////// debug/testing //////////////////////////////////
    // cout << "userInputChars.get() produces: "       << userInputChars.get()       << endl; // this prints whole thing (converts into string?)
    // cout << "userInputChars.get()[1] produces: "    << userInputChars.get()[1]    << endl; // this prints element in index 1
    // cout << "userInputChars[3] produces "   << *userInputChars[3]    << endl; // this prints whatever is in third index of userInput
    //////////////////////////////////////////////////////////////////////////////////

    // delete all :: begoneTHOT()
    cleaningGnome(userInputChars, binString);
    return 0;
}

void cleaningGnome(unique_ptr<char[]> &userInputChars, string** binString){
    userInputChars.reset();

    for(int i = 0; i < sizeof(binString)/sizeof(binString[0]); i++ )
        delete [] binString[i];
}