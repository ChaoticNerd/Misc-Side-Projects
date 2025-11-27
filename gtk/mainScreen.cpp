#include "mainScreen.h"
#include "calcScores.h"
#include <cairomm/context.h>

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
    textFile.signal_clicked().connect(sigc::mem_fun(*this, &mainScreen::on_textFile_clicked));
    
    // button 2 (bar chart)
    barChart.set_label("Bar Chart");
    barChart.set_hexpand(true);
    barChart.set_vexpand(true);
    barChart.set_size_request(20, 20);
    barChart.signal_clicked().connect(sigc::mem_fun(*this, &mainScreen::on_barChart_clicked));
    
    // button 3 (pie chart)
    pieChart.set_label("Pie Chart");
    pieChart.set_hexpand(true);
    pieChart.set_vexpand(true);
    pieChart.set_size_request(20, 20);
    pieChart.signal_clicked().connect(sigc::mem_fun(*this, &mainScreen::on_pieChart_clicked));

    // button 4 (sort) -- leads to drop-down menu type of thing
    sortBy.set_label("Sort by:");
    sortBy.set_hexpand(true);
    sortBy.set_vexpand(true);
    sortBy.set_size_request(20, 20);
    sortBy.signal_clicked().connect(sigc::mem_fun(*this, &mainScreen::on_sortBy_clicked));

    // add buttons into box in order
    buttonBox.append(textFile);
    buttonBox.append(barChart);
    buttonBox.append(pieChart);
    buttonBox.append(sortBy);

    // === Undertale-style message box ===
    battleText.set_text("* Hello.");
    battleText.set_halign(Gtk::Align::START);     // left-align text
    battleText.set_margin(5);

    // Put the label inside a frame that will become the white box
    battleFrame.set_child(battleText);
    battleFrame.set_hexpand(true);
    battleFrame.set_vexpand(false);

    // spacer fills all the top space
    spacer.set_vexpand(true);
    spacer.set_hexpand(true);

    // Attach: spacer row, then battleFrame, then buttonBox (Top -> Bot)
    screenGrid.attach(spacer,     0, 0); // grows to fill space
    screenGrid.attach(battleFrame,0, 1); // sits above buttons
    screenGrid.attach(buttonBox,  0, 2); // bottom row

    // puts box containing buttons onto screen
    set_child(screenGrid); 

    // Create and attach key controller
    key_controller = Gtk::EventControllerKey::create();
    add_controller(key_controller);

    // Connect key-pressed handler
    key_controller -> signal_key_pressed().connect(
        sigc::mem_fun(*this, &mainScreen::on_key_pressed),
        false
    );
}

void mainScreen::on_textFile_clicked(void) {
    openTextMenu();
}

void mainScreen::on_barChart_clicked(void) {
    // TODO: use score to compute data and show a bar chart window
    std::cout << "Bar chart button clicked.\n";
}

void mainScreen::on_pieChart_clicked(void) {
    // TODO: use score to compute data and show a pie chart window
    std::cout << "Pie chart button clicked.\n";
}

void mainScreen::on_sortBy_clicked(void) {
    openSortMenu();
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
        hide();       // close window  ->  exits app when last window
        return true;  // event handled
    }

    return false; // let other handlers run
}

void mainScreen::openTextMenu(void) {
    // Create an Undertale-style dialog in the center
    auto dialog = new Gtk::Dialog("Text File", *this);
    dialog -> set_name("ut-box");

    dialog -> set_modal(true);
    dialog -> set_decorated(false);           // no window frame = more "in-game"
    dialog -> set_default_size(400, 200);     // tweak for aesthetics

    // Content area acts like the white text box
    auto content = dialog -> get_content_area();
    content -> set_orientation(Gtk::Orientation::VERTICAL);
    content -> set_margin(20);

    auto label = Gtk::make_managed<Gtk::Label>("* What do you want to do with a text file?");
    label -> set_halign(Gtk::Align::START);
    content -> append(*label);

    // Buttons act like the Undertale menu options
    dialog ->add_button("Generate Random Scores",   1);
    dialog ->add_button("View Raw Text File", 2);
    dialog ->add_button("Upload File",   3);

    // Hook response → your handler
    dialog ->signal_response().connect(
        sigc::bind(
            sigc::mem_fun(*this, &mainScreen::textFileMenuResponse),
            dialog
        )
    );

    dialog ->show();
}

void mainScreen::openSortMenu(void) {
    // Create an Undertale-style dialog in the center
    auto dialog = new Gtk::Dialog("Sort By", *this);
    dialog -> set_name("ut-box");

    dialog -> set_modal(true);
    dialog -> set_decorated(false);           // no window frame = more "in-game"
    dialog -> set_default_size(400, 200);     // tweak for aesthetics

    // Content area acts like the white text box
    auto content = dialog -> get_content_area();
    content -> set_orientation(Gtk::Orientation::VERTICAL);
    content -> set_margin(20);

    auto label = Gtk::make_managed<Gtk::Label>("* How do you want to sort?");
    label -> set_halign(Gtk::Align::START);
    content -> append(*label);

    // Buttons act like the Undertale menu options
    dialog -> add_button("Student ID",   1);
    dialog -> add_button("Letter Grade", 2);
    dialog -> add_button("Percentage",   3);

    // Hook response → your handler
    dialog -> signal_response().connect(
        sigc::bind(
            sigc::mem_fun(*this, &mainScreen::sortMenuResponse),
            dialog
        )
    );

    dialog -> show();
}

void mainScreen::sortMenuResponse(int response_id, Gtk::Dialog* dialog) {
    switch (response_id) {
        case 1:
            std::cout << "Sort by Student ID\n";
            // TODO: call your sorting code with "student ID" mode
            break;
        case 2:
            std::cout << "Sort by Letter Grade\n";
            // TODO: the letter-grade sort
            break;
        case 3:
            std::cout << "Sort by Percentage\n";
            // TODO: percentage sort
            break;
        default:
            break; // Cancel or unknown
    }

    delete dialog;
}

void mainScreen::textFileMenuResponse(int response_id, Gtk::Dialog* dialog) {
    switch (response_id) {
        case 1:
            std::cout << "Generate Random File\n";
            userOption = TextFileOption::GenFile;
            promptFilename();
            break;
        case 2:
            std::cout << "View Raw Text File\n";
            userOption = TextFileOption::ViewRaw;
            promptFilename();
            break;
        case 3:
            std::cout << "Upload File\n";
            userOption = TextFileOption::Upload;
            promptFilename();
            break;
        default:
            break; // Cancel or unknown
    }

    delete dialog;
}

void mainScreen::promptFilename(void){
    // Create dialog dynamically
    auto dialog = new Gtk::Dialog("Enter File Name", *this);
    dialog -> set_name("ut-box");
    
    dialog->set_modal(true);
    dialog->set_decorated(false);        // no OS title bar
    dialog->set_transient_for(*this);    // center over main window
    dialog->set_default_size(400, 200);  // tweak as you like

    dialog -> add_button("_Cancel", Gtk::ResponseType::CANCEL);
    dialog -> add_button("_OK",     Gtk::ResponseType::OK);

    // Create an Entry widget
    Gtk::Entry* entry = Gtk::make_managed<Gtk::Entry>();
    entry -> set_placeholder_text("example.txt");

    dialog -> get_content_area() -> append(*entry);

    dialog -> signal_response().connect(
        sigc::bind(
            sigc::mem_fun(*this, &mainScreen::filenameEntered),
            dialog,
            entry
        )
    );

    dialog -> show();
}

void mainScreen::filenameEntered(int response_id, Gtk::Dialog* dialog, Gtk::Entry* entry){
    if (response_id == Gtk::ResponseType::OK){
        std::string filename = entry -> get_text();

        // basic validation
        if (filename.size() < 4 || filename.substr(filename.size() - 4) != ".txt"){
            std::cerr << "Error: filename must end in .txt\n";
            battleText.set_text("Filename must end in .txt");
        } else {
            std::cout << "User entered filename: " << filename << "\n";
            // if(score.checkFile()){
            switch(userOption){
                case TextFileOption::ViewRaw:{
                    score.fileImportFromGTK(filename);
                    if(score.checkFile()){
                        battleText.set_text("* Viewing Raw Data");
                        viewRawText.present();
                        viewRawText.setText(score.readRawData());
                        }
                    break;
                }
                case TextFileOption::Upload:{
                    score.fileImportFromGTK(filename);
                    if(score.checkFile())
                        battleText.set_text("* File Uploaded");
                    break;
                }
                case TextFileOption::GenFile:{
                    randomScoreFile.generateReport(filename);
                    battleText.set_text("Generated Random Score File");
                    break;
                }
            }
                
            // }
        }
    }
    delete dialog; // required in gtkmm4
}

