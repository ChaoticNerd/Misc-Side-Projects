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

fstream inFile, userFile, inputFile;
string fileName, newPassword, viewReport, dropped;
vector<string> usernameBank, passwordBank;
vector<double> calculatedPercentages, averageScores;
vector<vector<vector<double>>> allGrades;
int studentNumber, userSelect, upload = 0, report = 0, isGradesDropped, totalAssignmentsDropped[5], totalAssignments[5];

int main(void){
    // Prompt initial login
    user_login(0, usernameBank, passwordBank);
    
    do{
        // Prints menu and gets user's input
        cout << printMenu() << endl;
        cin >> userSelect;

        switch (userSelect){
        // Generate fake data
        case 1: 
            generateReport();
            break;
        // Which score file to use
        case 2:
            fileName = uploadFile();
            userFile.open(fileName);
            upload = 1;
            break;
        // Generate grade report
        case 3:
            if (!upload){
                fileName = checkFile();
                userFile.open(fileName);
            } 
            report = 1;
            cout << "Would you like to view your grade report? (Y/N)" << endl;
            cin >> viewReport;
            if (viewReport == "Y"){
                cout << "With grades dropped? (Y/N)" << endl;
                cin >> dropped;
                cout << "What is your student number?" << endl;
                cin >> studentNumber;
                if(dropped == "Y"){
                    generateReportOneStudent(userFile, allGrades, totalAssignmentsDropped, totalAssignments, 1, studentNumber, calculatedPercentages, averageScores);
                }else if(dropped == "N"){
                    generateReportOneStudent(userFile, allGrades, totalAssignmentsDropped, totalAssignments, 0, studentNumber, calculatedPercentages, averageScores);
                }
            }
            printResults(calculatedPercentages, averageScores);
            upload = 0;
            userFile.close();
            break;
        // View grade report with and without dropped items
        case 4:
            if (report == 1){
                cout << "View report with grades dropped? (Y/N)" << endl;
                cin >> dropped;
                cout << "What is your student number?" << endl;
                cin >> studentNumber;
                if(dropped == "Y"){
                    generateReportOneStudent(userFile, allGrades, totalAssignmentsDropped, totalAssignments, 1, studentNumber, calculatedPercentages, averageScores);
                }else if(dropped == "N"){
                    generateReportOneStudent(userFile, allGrades, totalAssignmentsDropped, totalAssignments, 0, studentNumber, calculatedPercentages, averageScores);
                }
                printResults(calculatedPercentages, averageScores);
                upload = 0;
                userFile.close();
            } else {
                cout << "Please generate a grade report first using option 3." << endl;
            }
            break;
        // Show class average percentages for each category and average for total percentage
        case 5: 
            if (!upload){
                fileName = checkFile();
                userFile.open(fileName);
            } 
            cout << "View average percentages with grades dropped? (Y/N)" << endl;
            cin >> dropped;
            if(dropped == "Y"){
                generateReportClass(userFile, allGrades, totalAssignmentsDropped, totalAssignments, 1, calculatedPercentages, averageScores);
            }else if(dropped == "N"){
                generateReportClass(userFile, allGrades, totalAssignmentsDropped, totalAssignments, 0, calculatedPercentages, averageScores);
            }
            printClassResults(calculatedPercentages);
            upload = 0;
            userFile.close();
            break;
        // Log out 
        case 6:
            cout << "Logging out..." << endl;
            user_login(1, usernameBank, passwordBank);
        // Exit program
        case 7: 
            break;
        default: 
            cout << "Error occurred. Please try again." << endl;
            break;
        }
    }
    while(userSelect != 7);
        cout << "Bye bye!" << endl;
    return 0;
}
