#include <array>
#include <iostream>

using namespace std;

// Function prototypes
string getUserInput(void);
void processUserInput(string userInput);

string getUserInput(void){
    string userInput;
    cout << "Hello! Please type what you want to display." << endl;
    cin >> userInput;
}

void processUserInput(string userInput){
    char *userInputChars = new char[1];
    for(int i = 0; i < userInput.length(); i++){
        userInputChars[i] = userInput[i];
    }
}