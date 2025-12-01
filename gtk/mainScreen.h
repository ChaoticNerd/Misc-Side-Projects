#ifndef MAINSCREEN_H
#define MAINSCREEN_H
#include <gtkmm.h>
#include <cairomm/cairomm.h>
#include "calcScores.h"
#include "textViewer.h"
#include "randGen.h"

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
        bool is_fullscreen_ = false;
        bool userDropGrades = false;
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

        Glib::RefPtr<Gtk::EventControllerKey> key_controller;

        // custom classes
        calcScore  score;        // for grade calculations
        textViewer viewRawText; // to display the raw text
        RandGen    randomScoreFile;

        bool on_key_pressed(guint keyval, guint /*keycode*/, Gdk::ModifierType /*state*/);
        
        /// @brief File menu stuff
        void promptFilename(void);
        void filenameEntered(int response_id, Gtk::Dialog* dialog, Gtk::Entry* entry);
        void textFileMenuResponse(int response_id, Gtk::Dialog* dialog);
        void openTextMenu(void);

        // Sort menu stuff
        void sortMenuResponse(int response_id, Gtk::Dialog* dialog);
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
                             Gtk::CheckButton* dropYesBtn);

        // Draw callback for the bar chart
        void on_barChart_draw(const Cairo::RefPtr<Cairo::Context>& cr, int width, int height);
        // Chart callbacks (Pie)
        void openPieMenu(void);
};
#endif