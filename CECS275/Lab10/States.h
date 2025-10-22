#include <cstring>
#include <cctype>
#include <fstream>
#include <iostream> // delete this later

using namespace std;

// function prototypes
void punctuateNumbers(char *line);

void getState(const string fileName){
    fstream rfile;
    ofstream wfile("us_states_population_formatted.txt");
    char line[2000];
    char *formattedLine;
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
        punctuateNumbers(line);

        // time to space out the beginning of the string until it detects a number
        for(int i = 0; i < strlen(line); i++){
            if(isdigit(line[i])){
                break;
            }else if(ispunct(line[i]) ){
                line[i] = ' ';
            }
        }

        counter = 0;
        wfile << line << endl;
        // cout << line << endl;
        // cout << line;
        // delete [] formattedLine;
    }
    rfile.close();
    wfile.close();
}

void punctuateNumbers(char *line){
    int digitCount = 0;
    for(int i = strlen(line)-1; i > 0; i--){
            if(isdigit(line[i]) && isdigit(line[i-1])){
                digitCount++;
                // cout << "lets see what is being counted as a digit: " << line[i] << endl;
            }else{
                break;
            }
            if(digitCount == 3){
                // cout << "meep " << line[i] <<  endl;;
                memmove(&line[i+1], &line[i], strlen(line) + 2 ); // this breaks
                line[i] = ',';
                digitCount = 0;
                //cout << line[i] << endl;
                // cout << "changed line var: " << line <<endl;
                
            }
            
        }
        digitCount = 0;
}