#include "calcScores.h"

// helper functs
bool calcScore::nonemptyLine(const std::string& line) {
    for (size_t i = 0; i < line.size(); ++i) {
        char c = line[i];
        if (c != ' ' && c != '\t' && c != '\r' && c != '\n')
            return true;
    }
    return false;
}

double calcScore::sumVector(const std::vector<double>& v) {
    double s = 0.0;
    for (size_t i = 0; i < v.size(); ++i) {
        s += v[i];
    }
    return s;
}


// Sum of all but the smallest "dropCount" values (no std::sort).
// static double sumVectorDropped(const std::vector<double>& v, int dropCount) {
//     int n = (int)v.size();
//     if (n == 0) return 0.0;
//     if (dropCount <= 0) return sumVector(v);
//     if (dropCount >= n) return 0.0;

//     std::vector<double> tmp = v;  // local copy

//     // Selection sort ascending
//     for (int i = 0; i < n - 1; ++i) {
//         int minIdx = i;
//         for (int j = i + 1; j < n; ++j) {
//             if (tmp[j] < tmp[minIdx])
//                 minIdx = j;
//         }
//         if (minIdx != i) {
//             double t = tmp[i];
//             tmp[i] = tmp[minIdx];
//             tmp[minIdx] = t;
//         }
//     }

//     double s = 0.0;
//     for (int i = dropCount; i < n; ++i)
//         s += tmp[i];

//     return s;
// }


// constructors 
calcScore::calcScore() {
    isFileUploaded = false;
    classSize = 0;
    threshold = 0.0;
    studentID = 0;

    for (int i = 0; i < 5; ++i) {
        gradeWeights[i] = 0;
        totalAssignments[i] = 0;
        totalAssignmentsDropped[i] = 0;
    }
}

calcScore::calcScore(fstream inFile, string fileName, int studentID, int classSize) : 
                     inputFile(std::move(inFile)),
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

calcScore::~calcScore() {
    if (inputFile.is_open())
        inputFile.close();
}

// reset major vectors
void calcScore::vector_dumptruck(void) {
    calculatedPercentages.clear();
    averageScores.clear();
    calculatedClassPercentages.clear();
    allGrades.clear();
    studentIDs.clear();
    letterGrades.clear();
}

// ------------------------------------------------------------------------------------------------
// file stuff
void calcScore::fileImportFromGTK(const std::string& path) {
    if (inputFile.is_open())
        inputFile.close();

    fileName.clear();
    isFileUploaded = false;
    classSize = 0;

    const std::string DATA_DIR = "../data/";

    std::string fileLoc = path;
    bool hasSep = false;
    for (size_t i = 0; i < fileLoc.size(); ++i) {
        if (fileLoc[i] == '/' || fileLoc[i] == '\\') {
            hasSep = true;
            break;
        }
    }
    if (!hasSep) {
        fileLoc = DATA_DIR + fileLoc;
    }

    inputFile.open(fileLoc.c_str());
    if (!inputFile.is_open()) {
        std::cerr << "Error: could not open file: " << fileLoc << std::endl;
        return;
    }

    fileName = fileLoc;
    isFileUploaded = true;

    countStudentsInFile();

    inputFile.clear();
    inputFile.seekg(0);
}

int calcScore::checkFile(void) const {
    return (isFileUploaded && inputFile.is_open()) ? 1 : 0;
}

void calcScore::readGradeWeights(std::fstream& file){
    // File line format: "15 15 10 40 20"
    //   labs quizzes midterms project final
    // as 0.15, 0.15, 0.10, 0.40, 0.20
    double w[5];

    for (int i = 0; i < 5; ++i) {
        if (!(file >> w[i])) {
            std::cerr << "Failed to read grade weights from file.\n";
            return;
        }
    }

    // Convert percentages → decimals
    for (int i = 0; i < 5; ++i)
        gradeWeights[i] = w[i] / 100.0;
}


std::string calcScore::readRawData(void) {
    std::string formatted;
    std::string line;

    if (!inputFile.is_open())
        return "<No file open>\n";

    inputFile.clear();
    inputFile.seekg(0);

    while (std::getline(inputFile, line)) {
        formatted += line;
        formatted += '\n';
    }

    inputFile.clear();
    inputFile.seekg(0);
    return formatted;
}

void calcScore::countStudentsInFile(void) {
    if (!inputFile.is_open()) {
        classSize = 0;
        return;
    }

    inputFile.clear();
    inputFile.seekg(0);

    std::string line;
    // Skip first 4 lines
    int headerLines = 4;
    for (int i = 0; i < headerLines; ++i) {
        if (!std::getline(inputFile, line)) {
            classSize = 0;
            return;
        }
    }

    int count = 0;
    while (std::getline(inputFile, line)) {
        if (nonemptyLine(line))
            ++count;
    }

    classSize = count;

    inputFile.clear();
    inputFile.seekg(0); //ove cursor back to beginning
}

// ------------------------------------------------------------------------------------------------

void calcScore::getTotalAssignments(fstream& file, int (&totalAssignmentsArray)[5]) {
    for (int i = 0; i < 5; ++i) {
        file >> totalAssignmentsArray[i];
    }
}

void calcScore::populateGradeVector(int (&totalAssignmentAmount)[5],
                                    vector<vector<vector<double>>>& grades,
                                    int amountOfStudents) {
    grades.clear();
    // +1: row 0 is max scores, rows 1..amountOfStudents are students
    for (int s = 0; s < amountOfStudents + 1; ++s) {
        vector<vector<double>> student;
        for (int cat = 0; cat < 5; ++cat) {
            vector<double> category(totalAssignmentAmount[cat], 0.0);
            student.push_back(category);
        }
        grades.push_back(student);
    }
}

void calcScore::populateStudentVector(int (&totalAssignmentAmount)[5],
                                      vector<vector<double>>& grades,
                                      int amountOfStudents) {
    (void)totalAssignmentAmount; // not actually needed for shape
    grades.clear();
    for (int s = 0; s < amountOfStudents; ++s) {
        vector<double> row(5, 0.0);
        grades.push_back(row);
    }
}

void calcScore::getPoints(fstream& file, vector<vector<vector<double>>>& grades)
{
    // grades[0] is the "max scores" row
    // grades[1..N] are per-student rows
    if (grades.empty())
        return;

    studentIDs.clear();

    int nStudents = static_cast<int>(grades.size()) - 1;

    // 1) Read max scores line into grades[0]
    for (int cat = 0; cat < 5; ++cat) {
        for (size_t k = 0; k < grades[0][cat].size(); ++k) {
            file >> grades[0][cat][k];
        }
    }

    // 2) For each student: ID + all category scores
    for (int s = 1; s <= nStudents; ++s) {
        int id = 0;
        file >> id;
        studentIDs.push_back(id);

        for (int cat = 0; cat < 5; ++cat) {
            for (size_t k = 0; k < grades[s][cat].size(); ++k) {
                file >> grades[s][cat][k];
            }
        }
    }
}
 

void calcScore::dropLowestScore(vector<vector<vector<double>>>& grades, int typeOfAssignment) {
    if (typeOfAssignment < 0 || typeOfAssignment >= 5)
        return;

    // Row 0 is max scores, skip it
    int nStudents = (int)grades.size() - 1;
    for (int s = 1; s <= nStudents; ++s) {
        std::vector<double>& catGrades = grades[s][typeOfAssignment];
        int n = (int)catGrades.size();
        if (n <= 0) continue;

        // find index of minimum
        int minIdx = 0;
        for (int i = 1; i < n; ++i) {
            if (catGrades[i] < catGrades[minIdx])
                minIdx = i;
        }
        // erase one lowest
        catGrades.erase(catGrades.begin() + minIdx);
    }
}

void calcScore::getTotalScoresOfOneCategory(vector<vector<vector<double>>>& grades,
                                            int assignmentType,
                                            vector<vector<vector<double>>>& totalCategoryPoints) {
    if (assignmentType < 0 || assignmentType >= 5)
        return;

    int nStudents = (int)grades.size() - 1;
    for (int s = 1; s <= nStudents; ++s) {
        double sum = 0.0;
        const std::vector<double>& cat = grades[s][assignmentType];
        for (size_t k = 0; k < cat.size(); ++k) {
            sum += cat[k];
        }
        // students in totalCategoryPoints are 0..nStudents-1
        totalCategoryPoints[s - 1][assignmentType][0] = sum;
    }
}

void calcScore::getIndividualStudentPointsTotal(vector<vector<vector<double>>>& grades,
                                                int studentNumber, vector<double>& totals) {
    totals.clear();
    if (studentNumber < 0 || studentNumber >= (int)grades.size())
        return;

    for (int cat = 0; cat < 5; ++cat) {
        double sum = 0.0;
        const std::vector<double>& catGrades = grades[studentNumber][cat];
        for (size_t k = 0; k < catGrades.size(); ++k) {
            sum += catGrades[k];
        }
        totals.push_back(sum);
    }
}

void calcScore::calculatePercentage(double grade, double total, double gradeWeight, vector<double>& out) {
    double pct = 0.0;
    if (total > 0.0) {
        double raw = grade / total;          // 0..1
        pct = raw * gradeWeight;            // weighted contribution 0..1
    }
    out.push_back(pct);
}

void calcScore::calculateClassPercentage(const vector<vector<vector<double>>>& grade, const vector<double>& total,
                                         double gradeWeight, vector<vector<double>>& out, int assignmentType) {
    if (assignmentType < 0 || assignmentType >= 5)
        return;

    // Use the size of 'out' (students), not 'grade' (which has an extra row)
    int numStudents = (int)out.size();

    for (int i = 0; i < numStudents; ++i) {
        double pts = grade[i][assignmentType][0];   // total points this student earned
        double maxPts = total[assignmentType];         // total possible points for category

        double contrib = 0.0;
        if (maxPts > 0.0) {
            double raw = pts / maxPts;   // fraction 0..1
            contrib    = raw * gradeWeight;
        }
        out[i][assignmentType] = contrib; // safe: i < out.size()
    }
}


void calcScore::getAverageOfCategory(double pointsEarned, int amountOfAssignments, vector<double>& avgOfCategory) {
    if (amountOfAssignments <= 0)
        avgOfCategory.push_back(0.0);
    else
        avgOfCategory.push_back(pointsEarned / (double)amountOfAssignments);
}

void calcScore::getAverageOfCategoryOfClass(const vector<vector<double>>& calculated, int assignmentType, vector<double>& averageOfSingleCategory) {
    double sum = 0.0;
    int count = 0;
    for (size_t i = 0; i < calculated.size(); ++i) {
        if ((int)calculated[i].size() > assignmentType) {
            sum += calculated[i][assignmentType];
            count++;
        }
    }
    if (count > 0)
        averageOfSingleCategory.push_back(sum / (double)count);
    else
        averageOfSingleCategory.push_back(0.0);
}

// Computes TOTAL weighted percentage for each student.
//
// Input row (before):
//   [ lab%, quiz%, exam%, project%, final% ]
//
// Output row (after):
//   [ lab%, quiz%, exam%, project%, final%, TOTAL% ]
//
// TOTAL% is simply the sum of the 5 category percentages.
void calcScore::getTotalPercentage(std::vector<std::vector<double>>& classPercentages) {
    for (size_t i = 0; i < classPercentages.size(); ++i) {
        double total = 0.0;

        // only the first 5 entries: lab..final
        for (int cat = 0; cat < 5 && cat < (int)classPercentages[i].size(); ++cat) {
            total += classPercentages[i][cat];
        }

        // store TOTAL at index 5
        classPercentages[i].push_back(total);
    }
}


// ------------------------------------------------------------------------
// letter grade stuff (tons bc simplifying all would take too long)
char calcScore::letterFromTotal(double total) const {
    // total is 0..1
    if (total >= GradeA)      return 'A';
    else if (total >= GradeB) return 'B';
    else if (total >= GradeC) return 'C';
    else if (total >= GradeD) return 'D';
    else                      return 'F';
}

void calcScore::computeLetterGrades(void) {
    letterGrades.clear();
    letterGrades.reserve(calculatedClassPercentages.size());

    for (size_t i = 0; i < calculatedClassPercentages.size(); ++i) {
        const std::vector<double>& row = calculatedClassPercentages[i];
        double total = 0.0;
        if (row.size() >= 6)
            total = row[5];
        else
            total = sumVector(row);

        letterGrades.push_back(letterFromTotal(total));
    }
}

std::string calcScore::getLetterGrade(vector<double>& percentages) {
    double total = sumVector(percentages); // 0..1
    percentages.push_back(total);
    char g = letterFromTotal(total);
    return std::string(1, g);
}

std::string calcScore::getLetterGradeSorted(const vector<double>& percentages) {
    double total = 0.0;
    if (percentages.size() > 5)
        total = percentages[5];
    else
        total = sumVector(percentages);
    char g = letterFromTotal(total);
    return std::string(1, g);
}

// ------------------------------------------------------------------------
// SORTS
void calcScore::bubbleSort(std::vector<std::vector<double>>& classPercentages) {
    int n = (int)classPercentages.size();
    if (n <= 1) return;

    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - 1 - i; ++j) {
            double ta = 0.0, tb = 0.0;
            if (classPercentages[j].size() > 5)
                ta = classPercentages[j][5];
            if (classPercentages[j+1].size() > 5)
                tb = classPercentages[j+1][5];
            if (tb > ta) {
                std::vector<double> tmp = classPercentages[j];
                classPercentages[j] = classPercentages[j+1];
                classPercentages[j+1] = tmp;
            }
        }
    }
}

void calcScore::sortByStudentID() {
    int n = (int)studentIDs.size();
    if (n <= 1) return;

    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - 1 - i; ++j) {
            if (studentIDs[j] > studentIDs[j + 1]) {
                int tID = studentIDs[j];
                studentIDs[j] = studentIDs[j + 1];
                studentIDs[j + 1] = tID;

                if (j < (int)letterGrades.size() && j + 1 < (int)letterGrades.size()) {
                    char tLG = letterGrades[j];
                    letterGrades[j] = letterGrades[j + 1];
                    letterGrades[j + 1] = tLG;
                }

                if (j < (int)calculatedClassPercentages.size() &&
                    j + 1 < (int)calculatedClassPercentages.size()) {
                    std::vector<double> tmp = calculatedClassPercentages[j];
                    calculatedClassPercentages[j] = calculatedClassPercentages[j+1];
                    calculatedClassPercentages[j+1] = tmp;
                }
            }
        }
    }
}

void calcScore::sortByLetterGrade() {
    int n = (int)letterGrades.size();
    if (n <= 1) return;

    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - 1 - i; ++j) {
            char la = letterGrades[j];
            char lb = letterGrades[j + 1];

            double ta = 0.0, tb = 0.0;
            if (j < (int)calculatedClassPercentages.size() &&
                calculatedClassPercentages[j].size() > 5)
                ta = calculatedClassPercentages[j][5];
            if (j+1 < (int)calculatedClassPercentages.size() &&
                calculatedClassPercentages[j+1].size() > 5)
                tb = calculatedClassPercentages[j+1][5];

            bool swapNeeded = false;
            if (la > lb) swapNeeded = true;
            else if (la == lb && ta < tb) swapNeeded = true;

            if (swapNeeded) {
                char tLG = letterGrades[j];
                letterGrades[j] = letterGrades[j + 1];
                letterGrades[j + 1] = tLG;

                if (j < (int)studentIDs.size() && j+1 < (int)studentIDs.size()) {
                    int tID = studentIDs[j];
                    studentIDs[j] = studentIDs[j+1];
                    studentIDs[j+1] = tID;
                }

                if (j < (int)calculatedClassPercentages.size() &&
                    j+1 < (int)calculatedClassPercentages.size()) {
                    std::vector<double> tmp = calculatedClassPercentages[j];
                    calculatedClassPercentages[j] = calculatedClassPercentages[j+1];
                    calculatedClassPercentages[j+1] = tmp;
                }
            }
        }
    }
}

void calcScore::sortByTotalPerc(void) {
    int n = (int)calculatedClassPercentages.size();
    if (n <= 1) return;

    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - 1 - i; ++j) {
            double ta = 0.0, tb = 0.0;
            if (calculatedClassPercentages[j].size() > 5)
                ta = calculatedClassPercentages[j][5];
            if (calculatedClassPercentages[j+1].size() > 5)
                tb = calculatedClassPercentages[j+1][5];

            if (tb > ta) {
                std::vector<double> tmp = calculatedClassPercentages[j];
                calculatedClassPercentages[j] = calculatedClassPercentages[j+1];
                calculatedClassPercentages[j+1] = tmp;

                if (j < (int)studentIDs.size() && j+1 < (int)studentIDs.size()) {
                    int tID = studentIDs[j];
                    studentIDs[j] = studentIDs[j+1];
                    studentIDs[j+1] = tID;
                }
                if (j < (int)letterGrades.size() && j+1 < (int)letterGrades.size()) {
                    char tLG = letterGrades[j];
                    letterGrades[j] = letterGrades[j+1];
                    letterGrades[j+1] = tLG;
                }
            }
        }
    }
}

// ------------------------------------------------------------------------
// GENERATE REPORTS
void calcScore::generateReportClass(int classSizeParam, int sortSelect, int isGradesDropped)
{
    if (!inputFile.is_open()) {
        std::cerr << "generateReportClass: inputFile is not open\n";
        return;
    }

    // Figure out how many students we actually have
    int nStudents = classSize;
    if (nStudents <= 0 && classSizeParam > 0)
        nStudents = classSizeParam;
    if (nStudents <= 0) {
        countStudentsInFile();   // uses the file to set classSize
        nStudents = classSize;
    }
    if (nStudents <= 0) {
        std::cerr << "generateReportClass: class size is zero\n";
        return;
    }

    // Clear all previous computed data
    vector_dumptruck();

    // Start reading from the top of the file
    inputFile.clear();
    inputFile.seekg(0);

    // 1) Skip the weights line
    readGradeWeights(inputFile);

    // 2) Read counts: labs, quizzes, midterms, project, final
    getTotalAssignments(inputFile, totalAssignments);

    // 3) Read "drops" per category
    getTotalAssignments(inputFile, totalAssignmentsDropped);

    // 4) Now file is at the "max scores" line.
    //    We build allGrades with row 0 = max scores, rows 1..nStudents = students.
    populateGradeVector(totalAssignments, allGrades, nStudents);
    getPoints(inputFile, allGrades);    // fills max scores + student scores + studentIDs

    // Optionally drop lowest scores in each category
    if (isGradesDropped) {
        for (int cat = 0; cat < 5; ++cat) {
            int drops = totalAssignmentsDropped[cat];
            while (drops > 0) {
                dropLowestScore(allGrades, cat);
                totalAssignments[cat]--;   // one assignment fewer in that category
                --drops;
            }
        }
    }

    // Compute total possible points per category (from the max-scores row)
    std::vector<double> totalPointsPossible(5, 0.0);
    for (int cat = 0; cat < 5; ++cat) {
        const std::vector<double>& maxScores = allGrades[0][cat];
        double sum = 0.0;
        int count = totalAssignments[cat];
        for (int k = 0; k < count && k < (int)maxScores.size(); ++k) {
            sum += maxScores[k];
        }
        totalPointsPossible[cat] = sum;
    }

    // Prepare per-student percentages: nStudents rows × 6 columns
    // [0]=lab, [1]=quiz, [2]=midterms, [3]=project, [4]=final, [5]=TOTAL
    calculatedClassPercentages.clear();
    calculatedClassPercentages.resize(nStudents, std::vector<double>(6, 0.0));

    // For each student, compute category contributions
    for (int s = 0; s < nStudents; ++s) {
        int rowIndex = s + 1; // because row 0 is max scores

        double totalContrib = 0.0;  // sum of 5 components

        for (int cat = 0; cat < 5; ++cat) {
            const std::vector<double>& scores = allGrades[rowIndex][cat];
            double earned = 0.0;
            int count = totalAssignments[cat];

            for (int k = 0; k < count && k < (int)scores.size(); ++k) {
                earned += scores[k];
            }

            double maxPts = totalPointsPossible[cat];
            double contrib = 0.0;
            if (maxPts > 0.0) {
                double raw = earned / maxPts;      // fraction (0..1) for this category
                contrib = raw * gradeWeights[cat]; // weighted contribution to final grade
            }
            calculatedClassPercentages[s][cat] = contrib;
            totalContrib += contrib;
        }

        // store TOTAL in column 5
        calculatedClassPercentages[s][5] = totalContrib;
    }


    // Compute letter grades for each student
    computeLetterGrades();

    // Sorting, using your existing helpers
    switch (sortSelect) {
        case 1: // sort by student ID
            sortByStudentID();
            break;
        case 2: // sort by letter grade
            sortByLetterGrade();
            break;
        case 3: // sort by total percentage
            sortByTotalPerc();
            break;
        default:
            // no sorting
            break;
    }
}

void calcScore::generateReportOneStudent(int isGradesDropped, int studentIndex) {
    // Make sure class report is up to date
    int n = classSize;
    if (n <= 0) {
        countStudentsInFile();
        n = classSize;
    }
    generateReportClass(n, /*sortSelect*/ 0, isGradesDropped);

    calculatedPercentages.clear();

    if (studentIndex < 0 || studentIndex >= (int)calculatedClassPercentages.size())
        return;

    // Copy this student's 5 category contributions + total
    calculatedPercentages = calculatedClassPercentages[studentIndex];
}

// ------------------------------------------------------------------------
// THRESHOLD (DO WE STILL NEED THIS?)
void calcScore::threshScore(double thresh, int isHigh) {
    if (calculatedClassPercentages.empty()) {
        cout << "No class data.\n";
        return;
    }

    double t = thresh / TO_PERCENT; // convert % to fraction
    cout << "Students with total "
         << (isHigh ? ">=" : "<=") << " " << thresh << "%:\n";

    for (size_t i = 0; i < calculatedClassPercentages.size(); ++i) {
        if (calculatedClassPercentages[i].size() <= 5) continue;
        double total = calculatedClassPercentages[i][5];
        bool ok = isHigh ? (total >= t) : (total <= t);
        if (ok) {
            char letter = letterFromTotal(total);
            cout << "  " << std::fixed << std::setprecision(2)
                 << total * TO_PERCENT << "%  (" << letter << ")\n";
        }
    }
    cout << "\n";
}

void calcScore::testPrintVector(vector<vector<double>>& v) {
    cout << "Vector dump:\n";
    for (size_t i = 0; i < v.size(); ++i) {
        for (size_t j = 0; j < v[i].size(); ++j)
            cout << v[i][j] << " ";
        cout << "\n";
    }
    cout << "\n";
}

// ------------------------------------------------------------------------
// setters / getters
void calcScore::setThreshold(int newThreshold) {
    threshold = (double)newThreshold / TO_PERCENT; // store as 0..1 fraction
}

void calcScore::setStudentID(int newStudentID) {
    studentID = newStudentID;
}

void calcScore::setClassSize(int newClassSize) {
    classSize = newClassSize;
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

const std::vector<std::vector<double>>& calcScore::getClassPercentages() const {
    return calculatedClassPercentages;
}

const std::vector<double>& calcScore::getAverageScores() const {
    return averageScores;
}

double calcScore::getGradeWeight(int category) const {
    if (category < 0 || category >= 5) return 0.0;
    return gradeWeights[category];
}
