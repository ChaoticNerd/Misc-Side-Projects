#include <array>
#include <iostream>
#include <memory>

using namespace std;

// Constant declarations
const string ESCAPE_CHARACTER = "\u001b[";
const string HIDE = "8";
const string GREEN_BACKGROUND = "42m";
const string WHITE_BACKGROUND = "47m";
const string RESET_CHARACTER = "0m";

// Function prototypes
string getUserWord(void);
void processUserInput(string userInput, unique_ptr<char>& userInputChars);
void showPixels(string** userInputBin);
/*
 * @author: Natasha Kho
 * @return: string containing user's input
 * @purpose: gets user input (can be ran multiple times if necessary)
*/
string getUserWord(void){
    string userInput;
    cout << "Hello! Please type what you want to display." << endl;
    cin >> userInput;
    return userInput;
}

int isBold(void){
    string balls;
    cout << "Do you want your word bolded? (Y/N)" << endl;
    cin >> balls;
    if(balls == "Y"){
        return 8;
    }
    return 5;
}

/*
 * @author: Natasha Kho
 * @return: char pointer showing where the 
            first location of the userInput broken up into individual
            chars is located
 * @brief: breaks down user's input into char array and returns 
            pointer to initial location
 * Honestly, never do this. literally just use a string variable.
*/
void processUserInput(string userInput, unique_ptr<char[]>& userInputChars){
    // allocate buffer with space for null terminator
    //userInputChars = make_unique<char[]>(userInput.length() + 1);
    
    // parsing user string into char*
    for(int i = 0; i < userInput.length(); i++){
        userInputChars[i] = userInput[i];
    }
    // null for last character
    userInputChars[userInput.length() + 1] = '\0';

}

// BullrOX
/*
 * @author: Natasha Kho
 # @param: User's input as binary string, ready to print
 * @brief: iterates through binary string and prints it out accordingly
*/
void showPixels(string** userInputBin, int column, int row){
    for(int i = 0; i < column; i++){ // CHARACTER (A,B,C,...)
        for(int j = 0; j < row; j++){ // WHICH HEX STRING TO ACCESS (A ROW 1, A ROW 2, A ROW 3, ...)
            // cout << ESCAPE_CHARACTER << HIDE << ';' << GREEN_BACKGROUND  << " ASDJKHASKJDAS " << ESCAPE_CHARACTER <<"0m" << endl;
            // cout << userInputBin[i][j] << endl;
            
            for(int k = 0; k < userInputBin[i][j].length(); k++){ // BINARY STRING ACCESS
                if(userInputBin[i][j][k] == '1')
                    cout << ESCAPE_CHARACTER << HIDE << ';' << GREEN_BACKGROUND << " " << ESCAPE_CHARACTER << RESET_CHARACTER;
                else
                    cout << ESCAPE_CHARACTER << HIDE << ';' << WHITE_BACKGROUND << " " << ESCAPE_CHARACTER << RESET_CHARACTER;
            }
            // each indent is the row of the letter
            cout << " ";
            
        }
        cout << endl;
    }
}

