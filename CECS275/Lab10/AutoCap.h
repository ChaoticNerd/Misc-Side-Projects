#include <cstring>
#include <cctype>
#include <fstream>

using namespace std;

// prototypes
void autoCap(char* userInput);
int isPunct(char x);

// open file in main
void autoCap(char* userInput){
    int punctDetected = 0;
    int firstLetterDetected = 0;

    int indexer = 0;
    while(userInput[indexer] != '\0'){
        
        // capitalizes first letter in string
        if(!firstLetterDetected && isalpha(userInput[indexer])){
            userInput[indexer] = toupper(userInput[indexer]);
            firstLetterDetected = 1;
        }

        // detects if there's punctuation
        if (isPunct(userInput[indexer])) {
            punctDetected = 1;
        }

        // capitalizes letter after punctuation
        if( isalpha(userInput[indexer]) && punctDetected){
            userInput[indexer] = toupper(userInput[indexer]);
            punctDetected = 0;
        }

        // detects if lone, lowercase i is present
        if(!isalpha(userInput[indexer-1]) && userInput[indexer] == 'i' && !isalpha(userInput[indexer+1]) )
            userInput[indexer] = toupper(userInput[indexer]);

        indexer++;
    }

}
// close file in main

/*
 * my own isPunct
*/
int isPunct(char x){
    if(x == '.' || x == '!' || x == '?')
        return 1;
    return 0;
}