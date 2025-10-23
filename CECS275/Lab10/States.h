#include <cstring>
#include <cctype>
#include <fstream>
#include <string>
#include <iostream> // delete this later

using namespace std;

// function prototypes
string punctuateNumbers(char *line);
int isComma(char x);

void getState(const string fileName){
    fstream rfile;
    ofstream wfile("us_states_population_formatted.txt");
    char line[2000];
    char *formattedLine = new char[2000];
    int punctCount = 0;
    int firstComma = 0;
    string stateName = "";
    string stateInitial = "";
    int stateNameLen = 0;
    string formattedPop = "";
    int hold = 0;
    rfile.open(fileName);
    // int digitCount = 0; // PUNCTUATE NUMBERS

    int counter = 0;
    while(rfile.getline(line, 2000, '\n')){
        // formattedLine = new char[strlen(line)]; 
        // strcpy(formattedLine,line);
        // cout << strlen(line) << endl;
        /*///////////////////////////////// PUNCTUATE NUMBERS ORIGIN PLACE //////////////////////////////////////////////////
        for(int i = strlen(line)-1; i > 0; i--){
            if(isdigit(line[i]) && isdigit(line[i-1])){
                digitCount++;
                // cout << "lets see what is being counted as a digit: " << line[i] << endl;
            }else{
                break;
            }
            if(digitCount == 3){
                // cout << "meep " << line[i] <<  endl;;
                memmove(&line[i+1], &line[i], strlen(line) + 2 );
                line[i] = ',';
                digitCount = 0;
                //cout << line[i] << endl;
                // cout << "changed line var: " << line <<endl;
                
            }
            
        }
        digitCount = 0;
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
        formattedPop = punctuateNumbers(line);

        // time to space out the beginning of the string until it detects a number
        for(int i = 0; i < strlen(line); i++){
            if(isalpha(line[i])){
                stateName += line[i]; 
                stateNameLen++;
            }else if(isdigit(line[i])){
                break;
            }else if(isComma(line[i])){
                firstComma++;
                if (firstComma==1){
                    for ( i = 0; i < (13 - stateNameLen);i++){
                        //cout << "i break in loop before" << endl;
                        stateName += " ";
                        //cout << "i break in loop" << endl;
                    }
                }
                //cout << "i break after loop" << endl;
                stateName += "               ";
                
            }else if(isspace(line[i])){
                stateName += " ";
            }
            if(firstComma){
                hold = i;
                break;
            }
        }
        cout << "HOLD: "<< hold << endl;
        firstComma = 0;
        for(int i = hold; i < hold + 2; i++){
            if(isalpha(line[i])){
                stateInitial += line[i]; 
            }else if(isdigit(line[i])){
                break;
            }else if(isComma(line[i])){
                //cout << "i break after loop" << endl;
                stateInitial += "               ";
            }else if(isspace(line[i])){
                stateInitial += " ";
            }
            if(firstComma){
                break;
            }
        }
        hold = 0;
        stateNameLen = 0;
        firstComma = 0;
        counter = 0;
        
        wfile << stateName + stateInitial + formattedPop << endl;
        stateName = "";stateInitial = "";
        formattedPop = "";
        // cout << line << endl;
        // cout << line;
        // delete [] formattedLine;
    }
    rfile.close();
    wfile.close();
}

/*
 * my own isPunct
*/
int isComma(char x){
    if( x == ',')
        return 1;
    return 0;
}

string punctuateNumbers(char *line){
    int digitCount = 0;
    string nums = "";
    for(int i = strlen(line)-1; i > 0; i--){
            if(isdigit(line[i])){
                digitCount++;
                nums.insert(0, 1, line[i]);
                // cout << "lets see what is being counted as a digit: " << line[i] << endl;
            }else{
                break;
            }
            if(digitCount == 3){
                
                //memmove(&line[i+1], &line[i], strlen(line) + 2 ); // this breaks
                // line[i] = ',';
                nums.insert(0, 1, ',');
                digitCount = 0;
                
            }
            
        }
        digitCount = 0;
        return nums;
}