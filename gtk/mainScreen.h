#ifndef MAINSCREEN_H
#define MAINSCREEN_H
#include <gtkmm.h>
#include <cairomm/cairomm.h>
#include <filesystem>
#include <cmath>
#include "calcScores.h"
#include "textViewer.h"
#include "randGen.h"
#include "DropGradeBtn.h"

enum class ChartKind {
    None,
    Bar,
    Pie
};


enum class TextFileOption{
    Upload,
    ViewRaw,
    GenFile
};

enum class SortByOption{
    NoSort,
    StudentID,
    LetterGrade,
    TotalPerc
};

enum class BarChartOption{
    TotalPercent,
    LabPercent,
    QuizPercent,
    ExamPercent,
    ProjectPercent,
    FinalPercent
};



class mainScreen : public Gtk::Window {
    public:
        mainScreen();
    
    private:
        TextFileOption userFileOption = TextFileOption::Upload;
        SortByOption userSortOption = SortByOption::NoSort;
        BarChartOption userBarChartOption = BarChartOption::TotalPercent;
        ChartKind currentChartKind = ChartKind::None;

        bool is_fullscreen_ = false;
        bool userDropGrades = false;
        std::vector<double> pieChartData;  // [A, B, C, D, F] as fractions
        int pieTotalStudents = 0;       

        Gtk::Button textFile, barChart, pieChart, sortBy;
        Gtk::Image textImg, barImg, pieImg, sortImg, menuSelectImg;
        Gtk::Label textLabel, barLabel, pieLabel, sortLabel;
        Gtk::Box buttonBox, temp;
        Gtk::Box spacer{Gtk::Orientation::VERTICAL};
        Gtk::Grid screenGrid, battleGrid; 
        Gtk::Frame battleFrame;
        Gtk::Label battleText;

        // Bar chart drawing on main screen
        Gtk::DrawingArea barChartArea;
        std::vector<double> barChartData;

        // For pie chart (A, B, C, D, F counts)
        std::vector<int> pieCounts;  // size 5 when used


        Glib::RefPtr<Gtk::EventControllerKey> key_controller;

        // custom classes
        calcScore  score;        // for grade calculations
        textViewer viewRawText; // to display the raw text
        textViewer viewSortedResults; // like viewRawText but for the sorted data
        RandGen    randomScoreFile;

        bool on_key_pressed(guint keyval, guint /*keycode*/, Gdk::ModifierType /*state*/);
        
        /// @brief File menu stuff
        void promptFilename(void);
        void filenameEntered(int response_id, Gtk::Dialog* dialog, Gtk::Entry* entry);
        void textFileMenuResponse(int response_id, Gtk::Dialog* dialog);
        void openTextMenu(void);
        void fileChooserResponse(int response_id, Gtk::FileChooserDialog* dialog);

        // Sort menu stuff
        void sortMenuResponse(int response_id, Gtk::Dialog* dialog, 
                              Gtk::CheckButton* studentID, Gtk::CheckButton* letterGrade, Gtk::CheckButton* percentages,
                              DropGradeBtn* gradeDropBtns);
        void openSortMenu(void);

        // button callback
        void on_textFile_clicked(void);
        void on_barChart_clicked(void);
        void on_pieChart_clicked(void);
        void on_sortBy_clicked(void);

        // Chart callbacks (Bar)
        void openBarMenu(void);
        void barMenuResponse(int response_id, Gtk::Dialog* dialog, Gtk::CheckButton* totalBtn, Gtk::CheckButton* labBtn,
                             Gtk::CheckButton* quizBtn, Gtk::CheckButton* examBtn, Gtk::CheckButton* projectBtn, Gtk::CheckButton* finalBtn,
                             DropGradeBtn* gradeDropBtns);

        // Draw callback for the bar chart
        void drawBarChart(const Cairo::RefPtr<Cairo::Context>& cr, int width, int height);

        // Chart callbacks (Pie)
        void openPieMenu(void);
        void pieMenuResponse(int response_id, Gtk::Dialog* dialog, DropGradeBtn* gradeDropBtns);
        void computePieFromCalcScore(void);   // helper that uses calcScore
        void drawPieChart(const Cairo::RefPtr<Cairo::Context>& cr, int width, int height); // draws the piechart

};
#endif