#include "calcScores.h"

// default constructor
calcScore::calcScore()
    : inputFile(),          // default-constructed, closed stream
      fileName(),           // empty string
      dropped(),
      threshold(0.10),      // matches usage as 0.x threshold
      studentID(0),
      classSize(40),
      isFileUploaded(false)
{
    std::fill(std::begin(totalAssignments),
              std::end(totalAssignments), 0);
    std::fill(std::begin(totalAssignmentsDropped),
              std::end(totalAssignmentsDropped), 0);

    calculatedPercentages.clear();
    averageScores.clear();
    calculatedClassPercentages.clear();
    allGrades.clear();
}


calcScore::~calcScore() {
    if (inputFile.is_open()) {
        inputFile.close();
    }
}


/*
 * Sorting algo
*/
void calcScore::bubbleSort(vector<vector<double>> &calculatedClassPercentages){
    size_t amtExchanged = 1;       // increment every time we have to swap two vectors
    size_t indexer = 1;            // increments before while check
    bool isSwap = true;

    do{
        if(indexer >= calculatedClassPercentages.size()){
            indexer = 1;        // restarts the indexer
            if(amtExchanged == 0){
                isSwap = false;
            }
            amtExchanged = 0;   // restarts the amtExchanged
            
        }
        // cout << "COMPARING: " << calculatedClassPercentages[indexer + 1][5] 
        //      << " WITH: "     << calculatedClassPercentages[indexer][5] << endl;

        // grabbing the 6th element as that's the total percentage for comparison and we can just sort using that
        if(calculatedClassPercentages[indexer][5] < calculatedClassPercentages[indexer - 1][5] ){
            // calculatedClassPercentages[indexer - 1].swap(calculatedClassPercentages[indexer]);
            swap(calculatedClassPercentages[indexer - 1], calculatedClassPercentages[indexer]);
            amtExchanged++;
            // cout << amtExchanged << endl;c
        }
        indexer++;
        //cout << "indexer why "<< indexer<<endl; 
        //cout << "WAS THERE ANYTHING EXCHANGED IN THIS TERM: " << amtExchanged << endl;
    }while(isSwap);
}

/*
 * isHigh: 1 = greater than
 * threshold input is 0.xxxxxx 
*/
void calcScore::threshScore(double threshold, int isHigh){
    size_t index = calculatedClassPercentages.size();
    
    // greater than
    if (isHigh){
        for(size_t i = 0; i < calculatedClassPercentages.size(); ++i){
            if(calculatedClassPercentages[i][5] >= threshold){
                index = i;
                break;
            }
        }
        if(index != calculatedClassPercentages.size())
            calculatedClassPercentages.erase(calculatedClassPercentages.begin(), calculatedClassPercentages.begin() + index);

    // less than    
    } else {
        for(size_t i = 0; i < calculatedClassPercentages.size(); ++i){
            if(calculatedClassPercentages[i][5] <= threshold){
                index = i;
                break;
            }
        }
        if(index != calculatedClassPercentages.size())
            calculatedClassPercentages.erase(calculatedClassPercentages.begin() + index, calculatedClassPercentages.end());

    }
    

}

void calcScore::getTotalPercentage(vector<vector<double>> &calculatedClassPercentages){
    for(size_t i = 0; i < calculatedClassPercentages.size(); i++){
        double tot = 0;
        for(double x : calculatedClassPercentages[i]){
            tot += x;
        }
        calculatedClassPercentages[i].push_back(tot);
    }
}

/*
 * @author Natasha Kho
*/
void calcScore::dropLowestScore(vector<vector<vector<double>>> (&allGrades), int typeOfAssignment){
    //int lowestScore = 0x7FFFFFFF; // this is the maximum int in hex

    // this iterates through all the students (41 total)
    for(size_t i = 0; i < allGrades.size(); i++ ){

        // this iterates through a student's assignment categories (5 total)
        for(size_t j = typeOfAssignment; j < allGrades[i].size(); j++){
            // cout << "function called" << endl;
            size_t indexToDrop = 0;     

            // cout << "STARTING NEW ITERATION: " << j << endl;

            // this iterates through a student's assignment's grades 
            // (ie. lab grades, then quiz grades, then exam grades, etc.)
            for(size_t k = 0; k < allGrades[i][j].size(); k++){
                // cout << "Where is K going: " << k << endl;
                // cout << allGrades[i][j].size() << " is the size of this shit." << endl;
                // if all of the current values of indexesToDrop are lower than the current value of allGrades, 
                // then it's added to get dropped
                if(allGrades[i][typeOfAssignment][indexToDrop] > allGrades[i][typeOfAssignment][k]){
                    // cout << "SETTING NEW K: " << k << endl;
                    indexToDrop = k;
                }
                
            }    
            //cout << "ERASING AT INDEX: " << indexToDrop << " WITH VALUE: " << allGrades[i][typeOfAssignment][indexToDrop] << endl;    
            // cout << "type of assignment: " << typeOfAssignment << endl;
            // cout << "FUCK " << allGrades[i][typeOfAssignment][indexToDrop] << endl;

            allGrades[i][typeOfAssignment].erase(allGrades[i][typeOfAssignment].begin() + indexToDrop);   
            break;
        }
    }
    
}

/*
 * @author: Natasha Kho
 * @param: filestream file variable
 * @param: amount of assignments to iterate through
 * @return total score of one category of assignment
*/
void calcScore::getPoints(fstream& file, vector<vector<vector<double>>> &allGrades){
    for(size_t i = 0; i < allGrades.size(); i++){
        for(size_t j = 0; j < allGrades[i].size(); j++){
            for(size_t k = 0; k < allGrades[i][j].size(); k++){
                file >> allGrades[i][j][k];
            }
        }
    }
    // for(int i = 0; i < totalAssignmentAmount; i++){
    //     file >> totalScoreArray[i];
    // }
}

/*
 * @author: Natasha Kho
 * @param: filestream file variable
 * @param: reference integer array of length 5
*/
void calcScore::getTotalAssignments(fstream& file, int (&totalAssignmentsArray)[5]){
    // First line of file
    for(size_t i = 0; i < 5; i++ ){
        file >> totalAssignmentsArray[i];
    }
    
}

/*
 * @author Natasha Kho
*/
void calcScore::populateGradeVector(int (&totalAssignmentAmount)[5], vector<vector<vector<double>>> &allGrades, int amountOfStudents){
    for(int i = 0; i < amountOfStudents + 1; i++){ // iterate 40 times because 40 students
        vector<vector<double>> studentScore; // Students' scores
        for(int j = 0; j < 5; j++){ // iterate 5 times because 5 categories per student
            vector<double> individualGrades;
            for(int k = 0; k < totalAssignmentAmount[j]; k++){ // iterates through amount of grades for each category
                individualGrades.push_back(0);
                // cout << individualGrades[k] << ' ';
            }
            studentScore.push_back(individualGrades);
            // cout << endl;
        }
         allGrades.push_back(studentScore); // pushing data for one student
                                            // allGrades[i] = push back needs to contain vector<vector<double>
    }
}

/*
 * @author Natasha Kho
 * overloaded
*/
void calcScore::populateStudentVector(int (&totalAssignmentAmount)[5], vector<vector<double>> &allGrades, int amountOfStudents){
    for(int i = 0; i < amountOfStudents + 1; i++){ // iterate 40 times because 40 students
        vector<double> studentScore; // Students' scores
        //cout << "Woah How many Students?!?!: " << i << "   ";
        for(long long unsigned int j = 0; j < sizeof(totalAssignmentAmount)/sizeof(totalAssignmentAmount[0]); j++){ // iterate 5 times because 5 categories per student
            
            studentScore.push_back(0);
            // cout << studentScore[j] << ' ';
        }
        // cout << endl;
        allGrades.push_back(studentScore); // pushing data for one student
                                            // allGrades[i] = push back needs to contain vector<vector<double>
    }
}

/*
 * @author: Natasha Kho
 * @param: total grade after calculations
 * @return letter grade based on score
*/
std::string calcScore::getLetterGrade(std::vector<double> &calculatedPercentages) {
    double totalGrade = 0.0;

    for (double x : calculatedPercentages) {
        totalGrade += x;
    }

    calculatedPercentages.push_back(totalGrade);

    if (totalGrade >= GradeA) {
        return "A";
    } else if (totalGrade >= GradeB){
        return "B";
    } else if (totalGrade >= GradeC){
        return "C";
    } else if (totalGrade >= GradeD){
        return "D";
    } else {
        return "F";
    }
}


std::string calcScore::getLetterGradeSorted(const vector<double>& calculatedPercentages){


    if (calculatedPercentages[5] >= GradeA) {
        return "A";
    } else if (calculatedPercentages[5] >= GradeB){
        return "B";
    } else if (calculatedPercentages[5] >= GradeC){
        return "C";
    } else if (calculatedPercentages[5] >= GradeD){
        return "D";
    } else {
        return "F";
    }
}

/*
 * @author: Natasha Kho
 * @param: actual points earned on total assignmenets
 * @param: total amount of points possible on assignment type
 * @return percentage of specific category
*/
void calcScore::calculatePercentage(double grade, double total, double gradeWeight, vector<double> &calculatedPercentages){
    // cout << "\nGrade we're inputting: " <<  grade
    //      << "\nTotal we're inputting: " << total << endl;
    calculatedPercentages.push_back((grade/total)*gradeWeight);
}

/*
 * @author: Natasha Kho
 * secret second author
*/
void calcScore::calculateClassPercentage( const std::vector<std::vector<std::vector<double>>> &grade, const std::vector<double> &total,
                                          double gradeWeight, std::vector<std::vector<double>> &calculatedPercentages, int assignmentType){
    double forklift = 0.0;

    for (size_t i = 0; i < grade.size(); i++) {
        forklift = 0.0;
        for (size_t j = 0; j < grade[i][assignmentType].size(); j++) {
            forklift += grade[i][assignmentType][j] / total[assignmentType] * gradeWeight;
        }
        calculatedPercentages[i].at(assignmentType) = forklift;
    }
}


/*
 * @author: Natasha Kho
 * for single student usage
*/
void calcScore::getAverageOfCategory(double pointsEarned, int amountOfAssignments, vector<double> &averageOfSingleCategory){
    averageOfSingleCategory.push_back(pointsEarned/amountOfAssignments);
}

/*
 * @author: Natasha Kho
 * for class average
*/
void calcScore::getAverageOfCategoryOfClass(const vector<vector<double>>& calculatedPercentages, int assignmentType, vector<double>& averageOfSingleCategory){
    double pointsEarned = 0; 
    for (size_t i = 0; i < calculatedPercentages.size(); i++){
        pointsEarned += calculatedPercentages[i][assignmentType];
    }
    
    averageOfSingleCategory.push_back(pointsEarned/classSize);
}

/*
 * @author: Natasha Kho
 * returns totalEarnedPoints (which is points earned in each category)
*/
void calcScore::getIndividualStudentPointsTotal(vector<vector<vector<double>>> &allGrades, int studentNumber, int (&totalAssignments)[5], vector<double> &totalEarnedPoints){
    vector<double> oneStudentScore;
    for(size_t i = studentNumber; i < allGrades.size(); i++){
        for(size_t j = 0; j < allGrades[studentNumber].size(); j++){
            for(size_t k = 0; k < allGrades[i][j].size(); k++){
                oneStudentScore.push_back(allGrades[studentNumber][j][k]);
            }
        }
        break;
    }

    // this totals the points earned in each category by the student 
    size_t cursor = 0;
    for(size_t assignmentInCategory: totalAssignments){
        double temp = 0;;
        //cout << "\nAssignment amount in Category: " << assignmentInCategory << endl;
        for(size_t i = 0; i < assignmentInCategory; i++){
            temp += oneStudentScore[cursor];
            cursor++;
        }
        totalEarnedPoints.push_back(temp);
    }
}

void calcScore::getTotalScoresOfOneCategory(vector<vector<vector<double>>> &allGrades, int assignmentType, vector<vector<vector<double>>> &totalCategoryPoints){
    vector<double> pointsEarnedForOneCategory;
    double temp = 0;
    //cout << "TEST1" << endl;
    for(size_t i = 1; i < allGrades.size(); i++){
        for(size_t j = 0; j < allGrades[assignmentType].size(); j++){
            for(size_t k = 0; k < allGrades[i][assignmentType].size(); k++){
                // cout << "TEST " << k << endl;
                temp += allGrades[i][assignmentType][k]; // adds each score of one category
                // cout << allGrades[i][assignmentType][k] << " + ";
            }
            // cout << "Total score of category: " << assignmentType << " is: " << temp << endl;

            pointsEarnedForOneCategory.push_back(temp); // puts total of one category into vector;
            temp = 0;
            break;
        }
    }

    // cout << "CHECKING POINTS EARNED FOR ONE CATEGORY VECTOR: " <<endl;
    // for(double x: pointsEarnedForOneCategory){
    //     cout << x << " ";
    // }
    // cout << endl;

    // cout << "Finish first for loop " << endl;

    // Sudo code to put into 3d vector of scores
    for(size_t i = 0; i < allGrades.size()-1; i++){ // this runs 40 times
        // cout << "Enter second for loop " << allGrades.size()-1 << endl;
        // cout << "Points earned in category vector: " << pointsEarnedForOneCategory[i] << endl;
        totalCategoryPoints[i][assignmentType].at(0) = pointsEarnedForOneCategory[i]; // this is not working correctly

        // totalCategoryPoints size is: 40 : 5 : 1
        // cout << "After putting data into Total Earned Points: " << totalCategoryPoints[i][assignmentType][1] <<endl;
        // line above states that we're putting in 0s only

    }
}

/*
 * @author: Natasha Kho
*/
void calcScore::generateReportClass(int classSize, int sortSelect, int isGradesDropped){
    // used for calculations
    vector<vector<vector <double>>> totalCategoryPoints;
    vector<double> totalPointsPossible;
    int temp[5] = {1, 1, 1, 1, 1};

    // First line of file
    getTotalAssignments(inputFile,totalAssignments);

    getTotalAssignments(inputFile,totalAssignmentsDropped);

    populateGradeVector(totalAssignments, allGrades, classSize);

    getPoints(inputFile, allGrades);

    populateGradeVector(temp, totalCategoryPoints, 39);
    populateStudentVector(temp, calculatedClassPercentages, 39);    
    if(isGradesDropped){
        // Do the stuff to drop the lowest grade as per requested wahoo!
        for(size_t i = 0; i < sizeof(totalAssignmentsDropped)/sizeof(totalAssignmentsDropped[0]); i++){
            int amtOfAssignmentsToDrop = totalAssignmentsDropped[i];
            while(amtOfAssignmentsToDrop){
                dropLowestScore( allGrades,i);
                amtOfAssignmentsToDrop--;
                totalAssignments[i]--;
            }
        }
    }

    // cout << "SOMEONE HELP ME, IM TOO GAY TO DO THIS" << endl; THIS PRINTS
    
    for(long long unsigned int i = 0; i < sizeof(totalAssignmentsDropped)/sizeof(totalAssignmentsDropped[0]); i++){ // goes for amount of categories there are
        getTotalScoresOfOneCategory(allGrades, i, totalCategoryPoints); // student score is totalEarnedPoints
    }


    getIndividualStudentPointsTotal(allGrades, 0, totalAssignments, totalPointsPossible);
    // cout << "before grade totalScores\n";
    // testPrintVector(allGrades);
    // for(double x: totalPointsPossible){
    //     cout << "SEEING INSIDE TOTAL POINTS POSSIBLE: " << x <<endl;
    // }

    // TODO: THIS PART BREAKS
    // this calculates the percentages for one student
    //  calculatePercentage(double grade, double total, double gradeWeight, vector<double> &calculatedPercentages)
    // this part requires testing
    for(size_t i = 0; i < allGrades.size() - 1; i++){ // this needs to iterate 40 times
        for(size_t j = 0; j < sizeof(totalAssignments)/sizeof(totalAssignments[0]); j++){ // iterates 5 times
            // cout << "SOMEONE HELP ME, IM TOO GAY TO DO THIS 0" << endl; // THIS PRINTS

            // this breaks on index 0
            calculateClassPercentage(totalCategoryPoints, totalPointsPossible, gradeWeights[j], calculatedClassPercentages, j);
            // cout << "SOMEONE HELP ME, IM TOO GAY TO DO THIS 1" << endl; // THIS PRINTS
            //cout << "COUNT: (" << i << " , " << j << ")  "<<calculatedPercentages[i][j]<< endl;
            // average scores should be size 5 vector
        }
    }
    // cout << "SOMEONE HELP ME, IM TOO GAY TO DO THIS" << endl; // THIS PRINTS

    for(size_t i = 0; i < sizeof(totalAssignments)/sizeof(totalAssignments[0]); i++){
        getAverageOfCategoryOfClass(calculatedClassPercentages, i, averageScores);
        // cout << "AVG SCORES: (" << i << " , " << j << ") "<< averageScores[i] <<endl; 
    }
    // cout << "amount of Average Scores: " << averageScores.size()<< endl; 
    // cout << "PERCENTAGES: " << endl;
    // for(int i = 0; i < calculatedPercentages.size(); i++){
    //     for(double x : calculatedPercentages[i]){
    //         cout << x << " ";
    //     }
    //     cout << endl;
    // }
    if (sortSelect == 1){
        getTotalPercentage(calculatedClassPercentages);
        bubbleSort(calculatedClassPercentages);
        // for(int i = 0; i < calculatedPercentages.size(); i++){
        //     for(int j = 0; j < calculatedPercentages[i].size(); j++){
        //             cout << calculatedPercentages[i][j] << " ";
                
        //     }
        //     cout << endl;
        // }
        
    }
    // cout << "AverageScores: " << endl;
    // for(double avgs : averageScores){
    //     cout << avgs << " ";
    // }
    // cout  << endl;
}

void calcScore::generateReportOneStudent(int isGradesDropped, int studentNumber){
    // First line of file
    getTotalAssignments(inputFile,totalAssignments);
    // for(int val: totalAssignments){
    //     cout << "Total Assignments: " << val  << endl;
    // }

    // Have a function to get amount of quiz/labs dropped
    getTotalAssignments(inputFile,totalAssignmentsDropped);
    // for(int val: totalAssignmentsDropped){
    //     cout << "Total Assignments Dropped: " << val  << endl;
    // }

    // cout << "===========================================\nPOPULATING POINTS POSSIBLE VECTOR" << endl;
    populateGradeVector(totalAssignments, allGrades, 40);
    // testPrintVector(allGrades); // should be a buncha 0s

    // cout << "===========================================\nINPUTTING POINTS" << endl;
    getPoints(inputFile, allGrades);
    // testPrintVector(allGrades); // PLEASE PRINT NUMBERS PLEAAAAAAASE

    // used for calculations
    vector<double> totalEarned;
    vector<double> totalPointsPossible;

    if(isGradesDropped){
        // Do the stuff to drop the lowest grade as per requested wahoo!
        for(size_t i = 0; i < sizeof(totalAssignmentsDropped)/sizeof(totalAssignmentsDropped[0]); i++){
        int amtOfAssignmentsToDrop = totalAssignmentsDropped[i];
            while(amtOfAssignmentsToDrop){
                //cout << "AT I: " << i << " ASSIGNMENT TO BE DROPPED DETECTED ::: " << totalAssignmentsDropped[i] << endl;
                dropLowestScore(allGrades, i);
                amtOfAssignmentsToDrop--;
                totalAssignments[i]--;
            }
        }
    }
    getIndividualStudentPointsTotal(allGrades, studentNumber, totalAssignments, totalEarned); // student score is totalEarnedPoints
    getIndividualStudentPointsTotal(allGrades, 0, totalAssignments, totalPointsPossible);

    for(size_t i = 0; i < totalEarned.size(); i++){
        calculatePercentage(totalEarned[i], totalPointsPossible[i], gradeWeights[i], calculatedPercentages);
        getAverageOfCategory(totalEarned[i], totalAssignments[i], averageScores);
    }
}

void calcScore::vector_dumptruck(void) {
    calculatedPercentages.clear();
    calculatedPercentages.shrink_to_fit();

    averageScores.clear();
    averageScores.shrink_to_fit();

    calculatedClassPercentages.clear();
    calculatedClassPercentages.shrink_to_fit();

    allGrades.clear();
    allGrades.shrink_to_fit();
}

/*
 * @author Natasha Kho
 * couts the report
 * @param: weighted project grade as decimal
*/
void calcScore::printResults(void){
    string letterGrade = getLetterGrade(calculatedPercentages);

    // // debug loop
    // cout << "Viewing Calculated Percentages" << endl;
    // for(double x : calculatedPercentages){
    //     cout << x << " ";
    // }
    // cout << endl;

    // cout << "Viewing Average Scores" << endl;
    // for(double x : averageScores){
    //     cout << x << " ";
    // }
    // cout << endl;

    cout << "===============================================\n" << setw(20) << "GRADES"           << "\n"
    << "Project: "      << setw(23) << fixed << setprecision(2) << calculatedPercentages[3] * TO_PERCENT    << "%\n" 
    << "Lab: "          << setw(27)                             << calculatedPercentages[0] * TO_PERCENT    << "%\n"
    << "Quiz: "         << setw(26)                             << calculatedPercentages[1] * TO_PERCENT    << "%\n"
    << "Exams: "        << setw(25)                             << calculatedPercentages[2] * TO_PERCENT    << "%\n"
    << "Final Exam: "   << setw(20)                             << calculatedPercentages[4] * TO_PERCENT    << "%\n"
    << "Total: "        << setw(25)                             << calculatedPercentages[5] * TO_PERCENT    << "%\n"
    << "Final Letter Grade: " << setw(10)                       << letterGrade                              << "\n"
    << "===============================================\n" << endl;

    cout << "===============================================\n" << setw(25) << "AVERAGE GRADES" << "\n"
    << "Project: "      << setw(23) << fixed << setprecision(2) << averageScores[3]             << "%\n" 
    << "Lab: "          << setw(27)                             << averageScores[0]             << "%\n"
    << "Quiz: "         << setw(26)                             << averageScores[1]             << "%\n"
    << "Exams: "        << setw(25)                             << averageScores[2]             << "%\n"
    << "Final Exam: "   << setw(20)                             << averageScores[4]             << "%\n"
    << "===============================================\n" << endl;
}

/*
 * @author Natasha Kho
 * averageScores is calculated for class Average this time
*/
void calcScore::printClassResults(void){
    double totalAvg = 0.0;
    for (double x : averageScores) {
        totalAvg += x;
    }
    
    cout << "===============================================\n" << setw(25) << "CLASS AVERAGES" << "\n"
         << "Project: "    << setw(23) << fixed << setprecision(2) << averageScores[3] * TO_PERCENT << "%\n" 
         << "Lab: "        << setw(27)                             << averageScores[0] * TO_PERCENT << "%\n"
         << "Quiz: "       << setw(26)                             << averageScores[1] * TO_PERCENT << "%\n"
         << "Exams: "      << setw(25)                             << averageScores[2] * TO_PERCENT << "%\n"
         << "Final Exam: " << setw(20)                             << averageScores[4] * TO_PERCENT << "%\n"
         << "Total: "      << setw(25)                             << totalAvg      * TO_PERCENT    << "%\n"
         << "===============================================\n" << endl;
}


/*
 * @author Natasha Kho
*/
void calcScore::printClassSortedResults(void){
    //NEEDS TO CALCULATE LETTER GRADE
    string letterGrade;
    cout << "===============================================\n" << setw(25) << "SORTED CLASS RESULTS" << "\n";
    for (size_t i = 0; i < calculatedClassPercentages.size(); i++){
        letterGrade = getLetterGradeSorted(calculatedClassPercentages[i]);
        cout << setw(7) <<  letterGrade << "       " << calculatedClassPercentages[i][5]<< endl;;
    }
    
    cout << "===============================================\n" << endl;
}


/*
 * @author: Natasha Kho
*/
void calcScore::printMenu(void){
    cout <<  "=========================================================\n"
    << "Select an option:\n"
    << "1. Generate fake data\n"
    << "2. Select which score file to use\n"
    << "3. Generate grade report\n"
    << "4. Show class average percentages\n"
    << "5. Sort class scores\n"
    << "6. Show scores above/below a threshold \n"
    << "7. Log Out\n"
    << "8. Exit program\n"
    << "=========================================================\n";
}

/*
 * @author: Natasha Kho
*/
void calcScore::fileImportFromGTK(const std::string& path){
    if (inputFile.is_open())
        inputFile.close();

     // Base data folder relative to where the program runs
    const std::string DATA_DIR = "../data/";   // or "data/" if that's your layout

    std::string fileLoc = path;

    // If the user just typed "grades.txt" (no / or \), prepend DATA_DIR
    if (fileLoc.find('/') == std::string::npos && fileLoc.find('\\') == std::string::npos){
        fileLoc = DATA_DIR + fileLoc;
    }

    inputFile.open(fileLoc);

    if (!inputFile.is_open()) {
        std::cerr << "Error: could not open file: " << fileLoc << std::endl;
        isFileUploaded = false;
        return;
    }
    std::cout << "File at " << fileLoc << " opened!" << std::endl;
    fileName = fileLoc;
    isFileUploaded = true;
}

std::string calcScore::readRawData(void){
    std::string formattedRawFile;
    std::string line;
    while(std::getline(inputFile, line)){
        formattedRawFile += line + '\n';
    }
    inputFile.clear();
    inputFile.seekg(0);
    std::cout << formattedRawFile;
    return formattedRawFile;
}

/*
 * @author: Natasha Kho
 * Used in succession after fileImport()
*/
int calcScore::checkFile(void){
    if(inputFile.is_open())
        return 1;
    return 0;
}


void calcScore::testPrintVector(vector<vector<double>> &allGrades){
    for(size_t i = 0; i < allGrades.size(); i++){
        for(size_t j = 0; j < allGrades[i].size(); j++){
                cout << allGrades[i][j] << " ";
            
        }
        cout << endl;
    }
}

/*
 * @author: Justin Narciso
 * 
*/
void calcScore::setThreshold(int newThreshold){
    this -> threshold = newThreshold;
}


/*
 * @author: Justin Narciso
 * 
*/
void calcScore::setStudentID(int newStudentID){
    this -> studentID = newStudentID;
}
/*
 * @author: Justin Narciso
 * 
*/
void calcScore::setClassSize(int newClassSize){
    this -> classSize = newClassSize;
}

/*
 * @author: Justin Narciso
 * 
*/
void calcScore::setTotalAssignmentsDropped(int (&newTotalAssignmentsDropped)[5]){
    this -> totalAssignmentsDropped[0] = newTotalAssignmentsDropped[0];
    this -> totalAssignmentsDropped[1] = newTotalAssignmentsDropped[1];
    this -> totalAssignmentsDropped[2] = newTotalAssignmentsDropped[2];
    this -> totalAssignmentsDropped[3] = newTotalAssignmentsDropped[3];
    this -> totalAssignmentsDropped[4] = newTotalAssignmentsDropped[4];
}

/*
 * @author: Justin Narciso
 * 
*/
void calcScore::setTotalAssignments(int (&newTotalAssignments)[5]){
    this -> totalAssignments[0] = newTotalAssignments[0];
    this -> totalAssignments[1] = newTotalAssignments[1];
    this -> totalAssignments[2] = newTotalAssignments[2];
    this -> totalAssignments[3] = newTotalAssignments[3];
    this -> totalAssignments[4] = newTotalAssignments[4];
}

void calcScore::setIsFileUploaded(bool FileUploaded){
    this -> isFileUploaded = FileUploaded;
}