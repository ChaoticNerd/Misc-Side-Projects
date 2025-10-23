#include <string>
#include <fstream>
#include "AutoCap.h"
#include "States.h"

const string FILENAME_STATES = "us_states_population.txt";

using namespace std;

int main(void){
    char *userChoice = new char[1];
    char *readFromFile = new char[20000];
    // char *userFileName;
    // ifstream rfile;
    // ofstream wfile;
    ifstream autoCapFileIn;
    ofstream autoCapFileOut;
    string fileNameIn;
    string fileNameOut;
    // cout << "Enter what you want fixed: " << endl;
    // cin.getline(userInput, 2000);

    // autoCap(userInput);
    // cout << userInput;

    do{
        // menu
        cout << "===================================================\n"
             << "1. Fix phrase from file.\n"
             << "2. Read data and format.\n"
             << "3. Leave program.\n"
             << "===================================================" 
             << endl;
        cin.getline(userChoice, 2);
        switch(userChoice[0]){
            case '1':
                //auto cap in here

                // read from:
                cout << "Please enter a file name to read from: ";
                cin >> fileNameIn;
                fileNameIn += ".txt";
                autoCapFileIn.open(fileNameIn);
                cin.ignore(1);
                // write to:
                cout << "Please enter file name to write to: ";
                cin >> fileNameOut;
                fileNameOut += ".txt";
                autoCapFileOut.open(fileNameOut);
                cin.ignore(1);
                // call autoCap for each line
                while(autoCapFileIn.getline(readFromFile, 20000, '\n')){
                    autoCap(readFromFile);
                    autoCapFileOut << readFromFile << endl;
                }
                autoCapFileIn.close();
                autoCapFileOut.close();
                break;
            case '2':
                // getState in here
                cout << "File generated." << endl;
                getState(FILENAME_STATES); // this is option 2
                break;
            case '3':
                cout << "fin." << endl;
                break;
        }
    
    } while(userChoice[0] != '3');

    return 0;
}