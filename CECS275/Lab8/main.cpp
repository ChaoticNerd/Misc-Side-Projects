/*
 * This program gives the user a choice between calculating their grades,
 * selecting which file to use, resetting their password, or generating fake scores
 * @author: Natasha Kho
 * @author: Emily Hsu
 * Created on: 2025-09-11
 * Last Modified: 2025-10-01
 * Reference: 
*/
#include "calcScores.h"
#include "login.h"

fstream inFile, inputFile;
string fileName, dropped;
vector<string> usernameBank, passwordBank;
vector<double> calculatedPercentages, averageScores;
vector<vector<double>> calculatedClassPercentages;
vector<vector<vector<double>>> allGrades;
int studentNumber, classSize, userSelect, upload = 0, report = 0, isGradesDropped, totalAssignmentsDropped[5], totalAssignments[5];
bool isFileUploaded = false;
const int AMOUNT_OF_CATEGORIES[5] = {1, 1, 1, 1, 1};

int main() {
    //initial log in
    user_login(0, usernameBank, passwordBank);

    do{
        printMenu();
        cin >> userSelect;

        switch(userSelect){

        //Random Generate Report
        case 1:
            generateReport();
            break;

        //Import Files
        case 2:
            fileImport(inputFile);
            break;
        
        //Solo student Report
        case 3: 
            checkFile(inputFile);
            cout << "With grades dropped? (Y/N)" << endl;
            cin >> dropped;
            cout << "What is your student number?" << endl;
            cin >> studentNumber;
            if(dropped == "Y"){
                generateReportOneStudent(inputFile, allGrades, totalAssignmentsDropped, totalAssignments, 1, studentNumber, calculatedPercentages, averageScores);
        
            } else if(dropped == "N"){
                generateReportOneStudent(inputFile, allGrades, totalAssignmentsDropped, totalAssignments, 0, studentNumber, calculatedPercentages, averageScores);
            }
            inputFile.close();
            printResults(calculatedPercentages, averageScores);
            break;

        //Class Average report
        case 4:
            checkFile(inputFile);
            cout << "With grades dropped? (Y/N)" << endl;
            cin >> dropped;
            cout << "What is your class size?" << endl;
            cin >> classSize;
            if(dropped == "Y"){
                generateReportClass(inputFile, classSize, allGrades, totalAssignmentsDropped, totalAssignments, 1, calculatedClassPercentages, averageScores); // to do BROKIE: uhhhhhh idk
            } else if(dropped == "N"){
                generateReportClass(inputFile, classSize, allGrades, totalAssignmentsDropped, totalAssignments, 0, calculatedClassPercentages, averageScores);
            }
            inputFile.close();
            printClassResults(averageScores);
            break;
            
        //empty for LAB8
        case 5:
            cout << "for Lab 8 Nothing now." << endl;
            break;
        //empty for LAB8
        case 6:
            cout << "for Lab 8 Nothing now." << endl;
            break;

        //doesnt break do-while, but logsout and repeats login function
        case 7:
            cout << "Bye Bye for now :D!" << endl;
            cout << "Logging out..." << endl;
            user_login(0, usernameBank, passwordBank);
            break;

        //TRUE exit program
        case 8:
            cout << "Bye for now :D!" << endl;
            break;

        }
    }while(userSelect != 8);
}
