/*
 * This C++ header declares the mainScreen class, which provides the main
 * application window for the Grade Calc program. It manages the chart views,
 * text file menus, sorting options, and profile display.
 * CECS 275 - Fall 2025
 * @author Justin Narciso
 * @author Natasha Kho
 * @version 3.0.2
 */

#ifndef MAINSCREEN_H
#define MAINSCREEN_H

#include <gtkmm.h>
#include <cairomm/cairomm.h>
#include <filesystem>
#include <cmath>
#include <pango/pangocairo.h> // custom fonts
#include "calcScores.h"
#include "textViewer.h"
#include "randGen.h"
#include "DropGradeBtn.h"
#include "profile.h"

// Chart type currently being displayed.
enum class ChartKind {
    None,
    Bar,
    Pie
};

// Options for handling text file operations.
enum class TextFileOption {
    Upload,
    ViewRaw,
    GenFile
};

// Different sorting categories for class data.
enum class SortByOption {
    NoSort,
    StudentID,
    LetterGrade,
    TotalPerc
};

// Options for bar chart categories.
enum class BarChartOption {
    TotalPercent,
    LabPercent,
    QuizPercent,
    ExamPercent,
    ProjectPercent,
    FinalPercent
};

/**
 * @class mainScreen
 * @brief Main application window for the Grade Calc program.
 *
 * This window provides the primary interface for navigating text file
 * operations, viewing charts, sorting data, and managing the profile box.
 * It supports dynamic bar and pie chart rendering using Cairo, menus for
 * selecting chart content, and dialogs for file operations.
 */
class mainScreen : public Gtk::Window {
public:

    /**
     * @brief Constructs the mainScreen for the given username.
     *
     * Initializes the layout, chart area, action buttons, Undertale-style
     * message box, and the profile/username panel.
     *
     * @param username The username to display in the profile box.
     */
    mainScreen(const Glib::ustring& username);
    
private:
    // State & Options 

    // Tracks which text file action the user selected.
    TextFileOption userFileOption = TextFileOption::Upload;

    // Tracks the sorting option chosen in the Sort menu.
    SortByOption userSortOption = SortByOption::NoSort;

    // Tracks the bar chart category selected by the user.
    BarChartOption userBarChartOption = BarChartOption::TotalPercent;

    // Indicates which chart (if any) is currently displayed.
    ChartKind currentChartKind = ChartKind::None;

    // Tracks fullscreen / windowed mode status.
    bool is_fullscreen_ = false;

    // Whether grade dropping (lowest assignment) is enabled.
    bool userDropGrades = false;

    // Fractional values for pie chart slices [A,B,C,D,F].
    std::vector<double> pieChartData;

    // Raw counts for A,B,C,D,F.
    std::vector<int> pieCounts;

    // Total number of students used to calculate pie chart.
    int pieTotalStudents = 0;

    // Main UI Widgets

    Gtk::Button textFile, barChart, pieChart, sortBy;
    Gtk::Label  textLabel, barLabel, pieLabel, sortLabel;
    Gtk::Box    buttonBox;
    Gtk::Box    spacer{Gtk::Orientation::VERTICAL};
    Gtk::Grid   screenGrid, battleGrid; 
    Gtk::Frame  battleFrame;
    Gtk::Label  battleText;

    // Drawing area for displaying bar/pie charts.
    Gtk::DrawingArea barChartArea;

    // Values used to render the bar chart.
    std::vector<double> barChartData;

    // Keyboard controller for fullscreen toggle and ESC close.
    Glib::RefPtr<Gtk::EventControllerKey> key_controller;

    // Helper Objects

    calcScore  score;              //< Handles grade calculations and data loading.
    textViewer viewRawText;        //< Displays raw text file data.
    textViewer viewSortedResults;  //< Displays sorted class report.
    RandGen    randomScoreFile;    //< Generates random score files.
    profileBox menuProfileBox;     //< Displays profile picture + username.

    // Event Handlers & Internal Logic 

    /**
     * @brief Handles keyboard shortcuts (F11 = fullscreen, ESC = exit).
     *
     * @param keyval GTK key value pressed.
     * @param keycode Unused.
     * @param state Modifier keys (unused).
     * @return true if the event was handled.
     */
    bool on_key_pressed(guint keyval, guint /*keycode*/, Gdk::ModifierType /*state*/);
    
    // Text File Menu 

    /**
     * @brief Opens a file chooser dialog prompting the user for a .txt file.
     */
    void promptFilename(void);

    /**
     * @brief Handles manual filename entry dialogs.
     *
     * @param response_id OK/CANCEL.
     * @param dialog Pointer to the dialog being handled.
     * @param entry The text entry containing the filename.
     */
    void filenameEntered(int response_id, Gtk::Dialog* dialog, Gtk::Entry* entry);

    /**
     * @brief Processes the user's selection in the Text File menu.
     *
     * @param response_id 1=Generate, 2=View Raw, 3=Upload.
     * @param dialog Pointer to the menu dialog.
     */
    void textFileMenuResponse(int response_id, Gtk::Dialog* dialog);

    /**
     * @brief Opens an Undertale-style dialog for text file operations.
     */
    void openTextMenu(void);

    /**
     * @brief Handles file chooser results for importing .txt files.
     *
     * @param response_id OK/CANCEL.
     * @param dialog The file chooser dialog.
     */
    void fileChooserResponse(int response_id, Gtk::FileChooserDialog* dialog);

    //  Sort Menu 

    /**
     * @brief Handles user selection in the Sort menu.
     */
    void sortMenuResponse(int response_id, Gtk::Dialog* dialog, 
                          Gtk::CheckButton* studentID,
                          Gtk::CheckButton* letterGrade,
                          Gtk::CheckButton* percentages,
                          DropGradeBtn* gradeDropBtns);

    /**
     * @brief Opens the sorting options dialog.
     */
    void openSortMenu(void);

    //  Button Callbacks 

    /**
     * @brief Opens text file actions menu.
     */
    void on_textFile_clicked(void);

    /**
     * @brief Opens bar chart options menu.
     */
    void on_barChart_clicked(void);

    /**
     * @brief Opens pie chart options menu.
     */
    void on_pieChart_clicked(void);

    /**
     * @brief Opens sorting options menu.
     */
    void on_sortBy_clicked(void);

    //  Bar Chart Logic 

    /**
     * @brief Opens the bar chart configuration dialog.
     */
    void openBarMenu(void);

    /**
     * @brief Handles bar chart configuration responses.
     */
    void barMenuResponse(int response_id, Gtk::Dialog* dialog,
                         Gtk::CheckButton* totalBtn, Gtk::CheckButton* labBtn,
                         Gtk::CheckButton* quizBtn, Gtk::CheckButton* examBtn,
                         Gtk::CheckButton* projectBtn, Gtk::CheckButton* finalBtn,
                         DropGradeBtn* gradeDropBtns);

    /**
     * @brief Draws a bar chart into the Cairo rendering context.
     *
     * @param cr Cairo drawing context.
     * @param width  Width of area.
     * @param height Height of area.
     */
    void drawBarChart(const Cairo::RefPtr<Cairo::Context>& cr,
                      int width, int height);

    //  Pie Chart Logic 

    /**
     * @brief Opens the pie chart configuration dialog.
     */
    void openPieMenu(void);

    /**
     * @brief Handles pie chart configuration responses.
     */
    void pieMenuResponse(int response_id, Gtk::Dialog* dialog,
                         DropGradeBtn* gradeDropBtns);

    /**
     * @brief Computes A/B/C/D/F distribution numbers and fractions.
     */
    void computePieFromCalcScore(void);

    /**
     * @brief Draws a pie chart using Cairo.
     *
     * @param cr Cairo drawing context.
     * @param width Chart area width.
     * @param height Chart area height.
     */
    void drawPieChart(const Cairo::RefPtr<Cairo::Context>& cr,
                      int width, int height);
        
    //  Profile Picture Dialog 

    /**
     * @brief Opens a file chooser to upload a profile image.
     */
    void on_pfpUpload_button_clicked();

    /**
     * @brief Handles the chosen image file from the profile picture dialog.
     *
     * @param response_id OK/CANCEL.
     * @param dialog File chooser dialog instance.
     */
    void fileChooserImageResponse(int response_id, Gtk::FileChooserDialog* dialog);
};

#endif // MAINSCREEN_H
