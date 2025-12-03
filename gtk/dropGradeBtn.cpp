#include "DropGradeBtn.h"
DropGradeBtn::DropGradeBtn() : Gtk::Box(Gtk::Orientation::VERTICAL), 
                               sepLabel("* Drop lowest scores?"),
                               dropNoBtn("No (use raw scores)"),
                               dropYesBtn("Yes (apply drops)") {
     // set up box to put buttons in
    set_spacing(10);
    set_margin(5);

    // Automatically adjust button box
    set_hexpand(true);
    set_vexpand(false);
    set_halign(Gtk::Align::FILL); // stretches horizontally
    set_valign(Gtk::Align::END); // puts at bottom of screen
    set_homogeneous(true); // all buttons same width

    // Divider
    sepLabel.set_margin_top(10);
    sepLabel.set_halign(Gtk::Align::START);

    // Creates Drop Grade? Buttons
    dropNoBtn.set_active(true);         // default no
    dropYesBtn.set_group(dropNoBtn);

    // Add buttons to box
    append(sepLabel);
    append(dropNoBtn);
    append(dropYesBtn);
}

bool DropGradeBtn::getGradeDropped() const{
    return dropYesBtn.get_active();
}

void DropGradeBtn::setGradeDropped(bool in){
    dropYesBtn.set_active(in);
    dropNoBtn.set_active(!in);
}