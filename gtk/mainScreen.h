#ifndef MAINSCREEN_H
#define MAINSCREEN_H
#include <gtkmm.h>
#include "calcScores.h"
#include "textViewer.h"
#include "randGen.h"

enum class TextFileOption{
    Upload,
    ViewRaw,
    GenFile
};

class mainScreen : public Gtk::Window {
    public:
        mainScreen();
    
    private:
        TextFileOption userOption = TextFileOption::Upload;
        bool is_fullscreen_ = true;
        Gtk::Button textFile, barChart, pieChart, sortBy;
        Gtk::Image textImg, barImg, pieImg, sortImg, menuSelectImg;
        Gtk::Label textLabel, barLabel, pieLabel, sortLabel;
        Gtk::Box buttonBox, temp;
        Gtk::Box spacer{Gtk::Orientation::VERTICAL};
        Gtk::Grid screenGrid, battleGrid; 
        Gtk::Frame battleFrame;
        Gtk::Label battleText;

        
        Glib::RefPtr<Gtk::EventControllerKey> key_controller;

        // custom classes
        calcScore  score;        // for grade calculations
        textViewer viewRawText; // to display the raw text
        RandGen    randomScoreFile;

        bool on_key_pressed(guint keyval, guint /*keycode*/, Gdk::ModifierType /*state*/);
        
        void promptFilename(void);
        void filenameEntered(int response_id, Gtk::Dialog* dialog, Gtk::Entry* entry);
        void textFileMenuResponse(int response_id, Gtk::Dialog* dialog);
        void openTextMenu(void);

        void sortMenuResponse(int response_id, Gtk::Dialog* dialog);
        void openSortMenu(void);


        void on_textFile_clicked(void);
        void on_barChart_clicked(void);
        void on_pieChart_clicked(void);
        void on_sortBy_clicked(void);

};
#endif