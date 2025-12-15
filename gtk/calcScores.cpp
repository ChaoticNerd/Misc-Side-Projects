/**
 * This C++ program implements grade-processing logic for calculating
 * student percentages, dropping scores, generating reports, and producing
 * sorted class results from a raw grade data file.
 *
 * CECS 275 - Fall 2025
 * @author Justin Narciso
 * @author Natasha Kho
 * @version 1.0.0
 */

#include "calcScores.h"
#include <cmath>


// CONSTRUCTORS / DESTRUCTOR  (Correct order to avoid -Wreorder warnings)
calcScore::calcScore()
    : threshold(0.0),
      studentID(0),
      classSize(0),
      isFileUploaded(false){
    for (int i = 0; i < 5; ++i) {
        gradeWeights[i] = 0;
        totalAssignments[i] = 0;
        totalAssignmentsDropped[i] = 0;
    }
}

calcScore::calcScore(fstream inFile, string fileName, int studentID, int classSize)
    : inputFile(std::move(inFile)),
      fileName(std::move(fileName)),
      threshold(0.0),
      studentID(studentID),
      classSize(classSize),
      isFileUploaded(false){
    for (int i = 0; i < 5; ++i) {
        gradeWeights[i] = 0;
        totalAssignments[i] = 0;
        totalAssignmentsDropped[i] = 0;
    }
}

calcScore::~calcScore(){
    if (inputFile.is_open())
        inputFile.close();
}

void calcScore::vector_dumptruck(){
    calculatedPercentages.clear();
    averageScores.clear();
    calculatedClassPercentages.clear();
    allGrades.clear();
    studentIDs.clear();
    letterGrades.clear();
}


// HELPER FUNCTIONS
bool calcScore::nonemptyLine(const std::string& line) {
    for (char c : line)
        if (!isspace(c))
            return true;
    return false;
}

double calcScore::sumVector(const std::vector<double>& v) {
    double sum = 0.0;
    for (double x : v)
        sum += x;
    return sum;
}


// FILE IMPORT / RAW DATA HANDLING
void calcScore::fileImportFromGTK(const std::string& path){
    if (inputFile.is_open())
        inputFile.close();

    fileName.clear();
    isFileUploaded = false;
    classSize = 0;

    const std::string DATA_DIR = "data/";
    std::string fileLoc = path;

    bool hasSep = false;
    for (char c : fileLoc)
        if (c == '/' || c == '\\') { hasSep = true; break; }

    if (!hasSep)
        fileLoc = DATA_DIR + fileLoc;

    inputFile.open(fileLoc.c_str());
    if (!inputFile.is_open()) {
        std::cerr << "ERROR: could not open file: " << fileLoc << "\n";
        return;
    }

    fileName = fileLoc;
    isFileUploaded = true;

    countStudentsInFile();

    inputFile.clear();
    inputFile.seekg(0);
}

int calcScore::checkFile() const {
    return (isFileUploaded && inputFile.is_open()) ? 1 : 0;
}

void calcScore::readGradeWeights(fstream& file){
    double w[5];
    for (int i = 0; i < 5; ++i) {
        if (!(file >> w[i])) {
            std::cerr << "ERROR: failed to read grade weights\n";
            return;
        }
    }
    for (int i = 0; i < 5; ++i)
        gradeWeights[i] = w[i] / 100.0;
}

std::string calcScore::readRawData(){
    if (!inputFile.is_open())
        return "<No file open>\n";

    std::string formatted, line;
    inputFile.clear();
    inputFile.seekg(0);

    while (std::getline(inputFile, line))
        formatted += line + '\n';

    inputFile.clear();
    inputFile.seekg(0);
    return formatted;
}

void calcScore::countStudentsInFile(){
    if (!inputFile.is_open()) {
        classSize = 0;
        return;
    }

    inputFile.clear();
    inputFile.seekg(0);

    std::string line;

    // Skip header lines
    for (int i = 0; i < 4; ++i)
        if (!std::getline(inputFile, line)) return;

    int count = 0;
    while (std::getline(inputFile, line))
        if (nonemptyLine(line)) ++count;

    classSize = count;

    inputFile.clear();
    inputFile.seekg(0);
}


// DATA VECTORS + POPULATION
void calcScore::getTotalAssignments(fstream& file, int (&arr)[5]){
    for (int i = 0; i < 5; ++i)
        file >> arr[i];
}

void calcScore::populateGradeVector(int (&amount)[5],
                                    vector<vector<vector<double>>>& grades,
                                    int nStudents){
    grades.clear();
    for (int s = 0; s < nStudents + 1; ++s) {
        vector<vector<double>> student;
        for (int c = 0; c < 5; ++c)
            student.emplace_back(amount[c], 0.0);
        grades.push_back(student);
    }
}

void calcScore::populateStudentVector(int (&)[5],
                                      vector<vector<double>>& grades,
                                      int nStudents){
    grades.clear();
    for (int i = 0; i < nStudents; ++i)
        grades.emplace_back(5, 0.0);
}

void calcScore::getPoints(fstream& file, vector<vector<vector<double>>>& grades){
    if (grades.empty()) return;

    studentIDs.clear();
    int nStudents = grades.size() - 1;

    // Read max scores
    for (int c = 0; c < 5; ++c)
        for (double& v : grades[0][c])
            file >> v;

    // Read student rows
    for (int s = 1; s <= nStudents; ++s) {
        int id;
        file >> id;
        studentIDs.push_back(id);

        for (int c = 0; c < 5; ++c)
            for (double& v : grades[s][c])
                file >> v;
    }
}


// DROP LOWEST SCORE
void calcScore::dropLowestScore(vector<vector<vector<double>>>& grades, int type)
{
    if (type < 0 || type >= 5) return;

    int nStudents = grades.size() - 1;
    for (int s = 1; s <= nStudents; ++s) {
        auto& cat = grades[s][type];
        if (cat.empty()) continue;

        size_t minIdx = 0;
        for (size_t i = 1; i < cat.size(); ++i)
            if (cat[i] < cat[minIdx])
                minIdx = i;

        cat.erase(cat.begin() + minIdx);
    }
}


// PERCENTAGE + LETTER GRADES
void calcScore::calculatePercentage(double grade, double total,
                                    double weight, vector<double>& out){
    double pct = (total > 0) ? (grade / total) * weight : 0.0;
    out.push_back(pct);
}

void calcScore::computeLetterGrades(){
    letterGrades.clear();
    for (auto& row : calculatedClassPercentages) {
        double total = row[5];
        letterGrades.push_back(letterFromTotal(total));
    }
}

char calcScore::letterFromTotal(double t) const{
    if (t >= GradeA) return 'A';
    if (t >= GradeB) return 'B';
    if (t >= GradeC) return 'C';
    if (t >= GradeD) return 'D';
    return 'F';
}


// MISSING FUNCTION (ADDED): getLetterGradeSorted()
string calcScore::getLetterGradeSorted(const vector<double>& percentages){
    double total = 0.0;

    if (percentages.size() > 5)
        total = percentages[5];
    else
        total = sumVector(percentages);

    return string(1, letterFromTotal(total));
}


// SORTING FUNCTIONS  (Correctly qualified to avoid linker errors)
void calcScore::sortByStudentID(){
    int n = studentIDs.size();
    for (int i = 0; i < n - 1; ++i)
        for (int j = 0; j < n - 1 - i; ++j)
            if (studentIDs[j] > studentIDs[j+1]) {

                std::swap(studentIDs[j], studentIDs[j+1]);
                std::swap(letterGrades[j], letterGrades[j+1]);
                std::swap(calculatedClassPercentages[j], calculatedClassPercentages[j+1]);
            }
}

void calcScore::sortByLetterGrade(){
    int n = letterGrades.size();
    for (int i = 0; i < n - 1; ++i)
        for (int j = 0; j < n - 1 - i; ++j)
            if (letterGrades[j] > letterGrades[j+1]) {
                std::swap(letterGrades[j], letterGrades[j+1]);
                std::swap(studentIDs[j], studentIDs[j+1]);
                std::swap(calculatedClassPercentages[j], calculatedClassPercentages[j+1]);
            }
}

void calcScore::sortByTotalPerc(){
    int n = calculatedClassPercentages.size();
    for (int i = 0; i < n - 1; ++i)
        for (int j = 0; j < n - 1 - i; ++j)
            if (calculatedClassPercentages[j][5] < calculatedClassPercentages[j+1][5]) {

                std::swap(calculatedClassPercentages[j], calculatedClassPercentages[j+1]);
                std::swap(studentIDs[j], studentIDs[j+1]);
                std::swap(letterGrades[j], letterGrades[j+1]);
            }
}


// GENERATE REPORTS
void calcScore::generateReportClass(int classSizeParam, int sortSelect, int isDropped){
    if (!inputFile.is_open()) {
        std::cerr << "ERROR: File not open.\n";
        return;
    }

    int nStudents = classSize;
    if (nStudents <= 0 && classSizeParam > 0)
        nStudents = classSizeParam;

    if (nStudents <= 0) {
        countStudentsInFile();
        nStudents = classSize;
    }

    vector_dumptruck();

    inputFile.clear();
    inputFile.seekg(0);

    readGradeWeights(inputFile);
    getTotalAssignments(inputFile, totalAssignments);
    getTotalAssignments(inputFile, totalAssignmentsDropped);

    populateGradeVector(totalAssignments, allGrades, nStudents);
    getPoints(inputFile, allGrades);

    if (isDropped) {
        for (int c = 0; c < 5; ++c) {
            int drops = totalAssignmentsDropped[c];
            while (drops-- > 0) {
                dropLowestScore(allGrades, c);
                totalAssignments[c]--;
            }
        }
    }

    vector<double> totalPossible(5, 0.0);

    for (int c = 0; c < 5; ++c) {
        double sum = 0.0;
        for (int k = 0; k < totalAssignments[c]; ++k)
            sum += allGrades[0][c][k];
        totalPossible[c] = sum;
    }

    calculatedClassPercentages.assign(nStudents, std::vector<double>(6, 0.0));

    for (int s = 0; s < nStudents; ++s) {
        double total = 0.0;
        for (int c = 0; c < 5; ++c) {
            double earned = 0.0;
            for (double score : allGrades[s+1][c])
                earned += score;

            double contrib = (totalPossible[c] > 0)
                ? (earned / totalPossible[c]) * gradeWeights[c]
                : 0.0;

            calculatedClassPercentages[s][c] = contrib;
            total += contrib;
        }
        calculatedClassPercentages[s][5] = total;
    }

    computeLetterGrades();

    switch (sortSelect) {
        case 1: sortByStudentID();   break;
        case 2: sortByLetterGrade(); break;
        case 3: sortByTotalPerc();   break;
    }
}

void calcScore::generateReportOneStudent(int isDropped, int studentIndex){
    if (classSize <= 0)
        countStudentsInFile();

    generateReportClass(classSize, 0, isDropped);

    calculatedPercentages.clear();
    if (studentIndex >= 0 && studentIndex < (int)calculatedClassPercentages.size())
        calculatedPercentages = calculatedClassPercentages[studentIndex];
}


// THRESHOLD FILTER PRINTING
void calcScore::threshScore(double thresh, int isHigh){
    if (calculatedClassPercentages.empty()) {
        cout << "No class data.\n";
        return;
    }

    double fraction = thresh / 100.0;

    cout << "Students with TOTAL "
         << (isHigh ? ">=" : "<=") << " " << thresh << "%\n";

    for (size_t i = 0; i < calculatedClassPercentages.size(); ++i) {
        double total = calculatedClassPercentages[i][5];

        if (isHigh ? (total >= fraction) : (total <= fraction)) {
            cout << "  " << total * 100.0 << "% ("
                 << letterFromTotal(total) << ")\n";
        }
    }
    cout << "\n";
}


// DEBUG VECTOR PRINT
void calcScore::testPrintVector(vector<vector<double>>& grid)
{
    cout << "Debug print:\n";
    for (auto& row : grid) {
        for (double v : row)
            cout << v << " ";
        cout << "\n";
    }
    cout << "\n";
}


// SETTERS / GETTERS
void calcScore::setThreshold(int newThreshold) {
    threshold = newThreshold / 100.0;
}

void calcScore::setStudentID(int id) {
    studentID = id;
}

void calcScore::setClassSize(int s) {
    classSize = s;
}

void calcScore::setTotalAssignmentsDropped(int (&arr)[5]) {
    for (int i = 0; i < 5; ++i)
        totalAssignmentsDropped[i] = arr[i];
}

void calcScore::setTotalAssignments(int (&arr)[5]) {
    for (int i = 0; i < 5; ++i)
        totalAssignments[i] = arr[i];
}

void calcScore::setIsFileUploaded(bool b) {
    isFileUploaded = b;
}

int calcScore::getClassSize() const {
    return classSize;
}

const vector<vector<double>>& calcScore::getClassPercentages() const {
    return calculatedClassPercentages;
}

const vector<double>& calcScore::getAverageScores() const {
    return averageScores;
}

double calcScore::getGradeWeight(int category) const{
    return (category >= 0 && category < 5) ? gradeWeights[category] : 0.0;
}


// STRING FORMATTING HELPERS
std::string calcScore::percentToDecimal(double fraction) const{
    double scaled = fraction * 1000.0;
    int iv = (int)std::round(scaled);

    int whole = iv / 10;
    int tenths = iv % 10;

    return std::to_string(whole) + "." + std::to_string(tenths);
}

std::string calcScore::padLeft(const std::string& s, int width) const{
    if ((int)s.size() >= width)
        return s.substr(0, width);
    return s + std::string(width - s.size(), ' ');
}

std::string calcScore::getClassReportString() const{
    if (calculatedClassPercentages.empty())
        return "ERROR\n";

    std::string out;

    out += padLeft("ID", 10);
    out += padLeft("Lab", 8);
    out += padLeft("Quiz", 8);
    out += padLeft("Exam", 8);
    out += padLeft("Proj", 8);
    out += padLeft("Final", 8);
    out += padLeft("Total%", 8);
    out += padLeft("LTTR", 4);
    out += "\n";

    out += "----------------------------------------------------------------\n";

    for (size_t i = 0; i < calculatedClassPercentages.size(); ++i) {

        int id = (i < studentIDs.size() ? studentIDs[i] : 0);
        char letter = (i < letterGrades.size() ? letterGrades[i] : '?');
        const auto& row = calculatedClassPercentages[i];

        out += padLeft(std::to_string(id), 10);
        out += padLeft(percentToDecimal(row[0]), 8);
        out += padLeft(percentToDecimal(row[1]), 8);
        out += padLeft(percentToDecimal(row[2]), 8);
        out += padLeft(percentToDecimal(row[3]), 8);
        out += padLeft(percentToDecimal(row[4]), 8);
        out += padLeft(percentToDecimal(row[5]), 8);
        out += padLeft(std::string(1, letter), 4);
        out += "\n";
    }

    return out;
}
