#include "textViewer.h"

textViewer::textViewer() {
    set_default_size(1250, 600);

    // create buffer and attach it to the member TextView
    buffer = Gtk::TextBuffer::create();
    textView.set_buffer(buffer);
    textView.set_editable(false);
    set_deletable(false);
    textView.set_wrap_mode(Gtk::WrapMode::WORD_CHAR);

    // scrolled window setup
    scrolledWindow.set_policy(Gtk::PolicyType::AUTOMATIC, Gtk::PolicyType::AUTOMATIC);
    scrolledWindow.set_child(textView);

    set_child(scrolledWindow);

    // key controller for ESC to close
    key_controller = Gtk::EventControllerKey::create();
    add_controller(key_controller);

    key_controller->signal_key_pressed().connect(
        sigc::mem_fun(*this, &textViewer::on_key_pressed),
        false
    );
}

void textViewer::setText(const std::string& text) {
    if (buffer) {
        buffer->set_text(text);
    }
}

bool textViewer::on_key_pressed(guint keyval, guint /*keycode*/, Gdk::ModifierType /*state*/) {
    if (keyval == GDK_KEY_Escape) {
        hide();
        return true;
    }
    return false;
}
