#include "mainScreen.h"

mainScreen::mainScreen(){
    set_title("Main Screen");
    set_default_size(800, 600);

    // setup grid for fullscreen
    screenGrid.set_halign(Gtk::Align::FILL);
    screenGrid.set_valign(Gtk::Align::FILL);

    // spacing between each grid element    
    screenGrid.set_margin(20);
    screenGrid.set_row_spacing(10);
    screenGrid.set_column_spacing(10);

    screenGrid.set_hexpand(true);
    screenGrid.set_vexpand(true);

    // set up box to put buttons in
    buttonBox.set_orientation(Gtk::Orientation::HORIZONTAL);
    buttonBox.set_spacing(10);
    buttonBox.set_margin(5);

    // Automatically adjust button box
    buttonBox.set_hexpand(true);
    buttonBox.set_vexpand(true);
    buttonBox.set_halign(Gtk::Align::FILL); // stretches horizontally
    buttonBox.set_valign(Gtk::Align::END); // puts at bottom of screen
    buttonBox.set_homogeneous(true); // all buttons same width

    // button 1 (text file)
    textFile.set_label("Text File");
    textFile.set_hexpand(true);
    textFile.set_vexpand(true);
    textFile.set_size_request(20, 20);
    
    // button 2 (bar chart)
    barChart.set_label("Bar Chart");
    barChart.set_hexpand(true);
    barChart.set_vexpand(true);
    barChart.set_size_request(20, 20);
    
    // button 3 (pie chart)
    pieChart.set_label("Pie Chart");
    pieChart.set_hexpand(true);
    pieChart.set_vexpand(true);
    pieChart.set_size_request(20, 20);

    // button 4 (sort) -- leads to drop-down menu type of thing
    sortBy.set_label("Sort by:");
    sortBy.set_hexpand(true);
    sortBy.set_vexpand(true);
    sortBy.set_size_request(20, 20);

    // add buttons into box in order
    buttonBox.append(textFile);
    buttonBox.append(barChart);
    buttonBox.append(pieChart);
    buttonBox.append(sortBy);

    // Puts button box into grid (I believe they're in descending (L -> R) order?)
    screenGrid.attach(buttonBox, 0, 550);

    // puts box containing buttons onto screen
    set_child(screenGrid); 

    // Create and attach key controller
    key_controller = Gtk::EventControllerKey::create();
    add_controller(key_controller);

    // Connect key-pressed handler
    key_controller->signal_key_pressed().connect(
        sigc::mem_fun(*this, &mainScreen::on_key_pressed),
        false
    );
}

bool mainScreen::on_key_pressed(guint keyval, guint /*keycode*/, Gdk::ModifierType /*state*/){
    if (keyval == GDK_KEY_F11) {
        if (is_fullscreen_)
            unfullscreen();
        else
            fullscreen();

        is_fullscreen_ = !is_fullscreen_;
        return true; // event handled
    }
    else if (keyval == GDK_KEY_Escape) {
        hide();       // close window -> exits app when last window
        return true;  // event handled
    }

    return false; // let other handlers run
}