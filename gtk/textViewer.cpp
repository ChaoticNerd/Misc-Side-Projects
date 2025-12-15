/**
 * This C++ program implements a text viewing window for displaying large
 * blocks of read-only text in a scrollable Gtk::TextView, with ESC to close.
 *
 * CECS 275 - Fall 2025
 * @author Justin Narciso
 * @author Natasha Kho
 */

#include "textViewer.h"

textViewer::textViewer(){
    set_default_size(1250, 600);

    // Create buffer and attach it to the TextView
    buffer = Gtk::TextBuffer::create();
    textView.set_buffer(buffer);
    textView.set_editable(false);
    set_deletable(false);
    textView.set_wrap_mode(Gtk::WrapMode::WORD_CHAR);

    // Scrolled window setup
    scrolledWindow.set_policy(Gtk::PolicyType::AUTOMATIC, Gtk::PolicyType::AUTOMATIC);
    scrolledWindow.set_child(textView);

    set_child(scrolledWindow);

    // Key controller for ESC to close window
    key_controller = Gtk::EventControllerKey::create();
    add_controller(key_controller);

    key_controller->signal_key_pressed().connect(
        sigc::mem_fun(*this, &textViewer::on_key_pressed),
        false
    );
}

void textViewer::setText(const std::string& text){
    if (buffer) {
        buffer->set_text(text);
    }
}

bool textViewer::on_key_pressed(guint keyval,
        guint /*keycode*/, Gdk::ModifierType /*state*/){
    if (keyval == GDK_KEY_Escape) {
        hide();   // Close the window
        return true;
    }
    return false;
}
