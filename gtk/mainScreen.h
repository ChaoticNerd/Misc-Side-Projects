#ifndef MAINSCREEN_H
#define MAINSCREEN_H
#include <gtkmm.h>
class mainScreen : public Gtk::Window {
    public:
        mainScreen();
    
    private:
        bool is_fullscreen_ = false;
        Gtk::Button textFile, barChart, pieChart, sortBy;
        Gtk::Box buttonBox;
        Gtk::Grid screenGrid; //USE THIS INSTEAD OF BOX
        Glib::RefPtr<Gtk::EventControllerKey> key_controller;

        bool on_key_pressed(guint keyval, guint /*keycode*/, Gdk::ModifierType /*state*/);


};
#endif