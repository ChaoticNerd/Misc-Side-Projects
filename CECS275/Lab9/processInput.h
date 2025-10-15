#include <array>
#include <iostream>

using namespace std;

// Function prototypes
string getUserInput(void);
char* processUserInput(string userInput);

/*
 * @author: Natasha Kho
 * @return: string containing user's input
 * @purpose: gets user input (can be ran multiple times if necessary)
*/
string getUserInput(void){
    string userInput;
    cout << "Hello! Please type what you want to display." << endl;
    cin >> userInput;
    return userInput;
}

/*
 * @author: Natasha Kho
 * @return: char pointer showing where the 
            first location of the userInput broken up into individual
            chars is located
 * @purpose: breaks down user's input into char array and returns 
            pointer to initial location
 * Honestly, never do this. literally just use a string variable.
*/
char* processUserInput(string userInput, char* userInputChars){
    
    // parsing user string into char*
    for(int i = 0; i < userInput.length(); i++){
        userInputChars[i] = userInput[i];
    }

    // null for last character
    userInputChars[userInput.length() + 1] = '\0';

    // returns char*
    return userInputChars;
}