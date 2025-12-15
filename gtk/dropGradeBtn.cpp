/**
 * This C++ program defines a GUI widget for selecting whether a grade is dropped
 * using a pair of Yes/No toggle buttons.
 * CECS 275 - Fall 2025
 * @author Justin Narciso
 * @author Natasha Kho
 * @version 1.0.0
 */
 
#include "DropGradeBtn.h"


// Constructor: Sets up the label and Yes/No buttons.
DropGradeBtn::DropGradeBtn() :
  Gtk::Box(Gtk::Orientation::VERTICAL),
  sepLabel("* Drop lowest scores?"),
  dropNoBtn("No (use raw scores)"),
  dropYesBtn("Yes (apply drops)"){
    // Box layout spacing and behavior
    set_spacing(10);
    set_margin(5);
    set_hexpand(true);
    set_vexpand(false);
    set_halign(Gtk::Align::FILL);
    set_valign(Gtk::Align::END);
    set_homogeneous(true);  // Make all items the same width

    // Label formatting
    sepLabel.set_margin_top(10);
    sepLabel.set_halign(Gtk::Align::START);

    // Check button group: No = default, Yes = grouped toggle
    dropNoBtn.set_active(true);
    dropYesBtn.set_group(dropNoBtn);

    // Add all elements to the box
    append(sepLabel);
    append(dropNoBtn);
    append(dropYesBtn);
}


// Returns true if the user selected "Yes" (grade is dropped).
bool DropGradeBtn::getGradeDropped() const {
    return dropYesBtn.get_active();
}


// Sets whether the grade should be dropped (true = yes, false = no).
void DropGradeBtn::setGradeDropped(bool in) {
    dropYesBtn.set_active(in);
    dropNoBtn.set_active(!in);
}
