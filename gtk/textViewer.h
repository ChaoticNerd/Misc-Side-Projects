#ifndef TEXTVIEWER_H
#define TEXTVIEWER_H

#include <gtkmm.h>

class textViewer : public Gtk::Window {
public:
    textViewer();

    // allow mainScreen to set the displayed text
    void setText(const std::string& text);

private:
    Gtk::ScrolledWindow scrolledWindow;
    Gtk::TextView textView;
    Glib::RefPtr<Gtk::TextBuffer> buffer;

    Glib::RefPtr<Gtk::EventControllerKey> key_controller;
    bool on_key_pressed(guint keyval, guint /*keycode*/, Gdk::ModifierType /*state*/);
};

#endif
