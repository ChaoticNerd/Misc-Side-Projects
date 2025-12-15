/*
 * This C++ header declares the mainScreen class, which provides the main
 * application window for the Grade Calc program. It manages the chart views,
 * text file menus, sorting options, and profile display.
 * CECS 275 - Fall 2025
 * @author Justin Narciso
 * @author Natasha Kho
 * @version 3.0.2
 */
#include "mainScreen.h"
#include <iostream>

// FONT STUFF
namespace {
    void draw_pango_text(const Cairo::RefPtr<Cairo::Context>& cr, const std::string& text,
                         double x, double y, int font_size, bool center = false){
        if (text.empty()) return;

        // Create Pango layout tied to Cairo context
        PangoLayout* layout = pango_cairo_create_layout(cr->cobj());
        pango_layout_set_text(layout, text.c_str(), -1);

        // Use the Undertale font  loaded in main.cpp
        PangoFontDescription* desc =
            pango_font_description_from_string(("Determination Mono " + std::to_string(font_size)).c_str());
        pango_layout_set_font_description(layout, desc);

        // CENTER FONT
        int w = 0, h = 0;
        pango_layout_get_pixel_size(layout, &w, &h);

        double drawX = x;
        double drawY = y;
        if (center) {
            drawX -= w / 2.0;
            drawY -= h / 2.0;
        }

        cr->save();
        cr->set_source_rgb(1.0, 1.0, 1.0); // white text
        cr->move_to(drawX, drawY);
        pango_cairo_show_layout(cr->cobj(), layout);
        cr->restore();

        // Cleanup
        g_object_unref(layout);
        pango_font_description_free(desc);
    }
}

mainScreen::mainScreen(const Glib::ustring& username):
    menuProfileBox(username){
    set_title("Main Screen");
    set_default_size(800, 1000);
    std::cout <<username<<std::endl;
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
    buttonBox.set_hexpand(false);
    buttonBox.set_vexpand(false);
    buttonBox.set_halign(Gtk::Align::CENTER); // stretches horizontally
    buttonBox.set_valign(Gtk::Align::END); // puts at bottom of screen
    buttonBox.set_homogeneous(true); // all buttons same width

    // Bar chart stuff
    barChartArea.set_vexpand(true);   // chart can grow vertically
    barChartArea.set_hexpand(true);   // chart stretches horizontally
    
    // button 1 (text file)
    //textFile.set_name("Text File");
    textFile.get_style_context()->add_class("Text-Button"); //reference to stly.css to do the orange and yellow buttons
    textFile.set_hexpand(true);
    textFile.set_vexpand(true);
    textFile.set_size_request(240, 92);
    textFile.signal_clicked().connect(sigc::mem_fun(*this, &mainScreen::on_textFile_clicked));
    //textFile.get_style_context()->add_class("TextFile"); //reference to stly.css to do the orange and yellow buttons
    
    // button 2 (bar chart)
    barChart.get_style_context()->add_class("Bar-Button"); //reference to stly.css to do the orange and yellow buttons
    barChart.set_name("Bar Chart");
    barChart.set_hexpand(true);
    barChart.set_vexpand(true);
    barChart.set_size_request(240, 92);
    barChart.signal_clicked().connect(sigc::mem_fun(*this, &mainScreen::on_barChart_clicked));
    
    // button 3 (pie chart)
    pieChart.get_style_context()->add_class("Pie-Button"); //reference to stly.css to do the orange and yellow buttons
    pieChart.set_name("Pie Chart");
    pieChart.set_hexpand(true);
    pieChart.set_vexpand(true);
    pieChart.set_size_request(240, 92);
    pieChart.signal_clicked().connect(sigc::mem_fun(*this, &mainScreen::on_pieChart_clicked));

    // button 4 (sort) -- leads to drop-down menu type of thing
    sortBy.get_style_context()->add_class("Sort-Button"); //reference to stly.css to do the orange and yellow buttons
    sortBy.set_name("Sort by:");
    sortBy.set_hexpand(true);
    sortBy.set_vexpand(true);
    sortBy.set_size_request(240, 92);
    sortBy.signal_clicked().connect(sigc::mem_fun(*this, &mainScreen::on_sortBy_clicked));

    // Connect draw function
    barChartArea.set_draw_func(sigc::mem_fun(*this, &mainScreen::drawBarChart));

    // add buttons into box in order
    buttonBox.append(textFile);
    buttonBox.append(barChart);
    buttonBox.append(pieChart);
    buttonBox.append(sortBy);

    // === Undertale-style message box ===
    battleText.get_style_context()->add_class("Battle-Text");
    battleText.set_text("* Hello.");
    battleText.set_halign(Gtk::Align::START);     // left-align text
    battleText.set_margin(5);

    // Put the label inside a frame that will become the white box
    battleFrame.get_style_context()->add_class("Battle-Frame");
    battleFrame.set_halign(Gtk::Align::CENTER);
    battleFrame.set_valign(Gtk::Align::END);
    battleFrame.set_child(battleText);
    battleFrame.set_hexpand(false);
    battleFrame.set_vexpand(false);
    battleFrame.set_size_request(960, 240);

    // spacer fills all the top space
    spacer.set_vexpand(false);
    spacer.set_hexpand(true);

    // textViewer stuff (viewSortedResults in the menu funct)
    viewRawText.set_title("Raw Text File");

    //set_child(menuProfileBox);
    menuProfileBox.set_hexpand(false);
    menuProfileBox.set_vexpand(false);
    menuProfileBox.set_halign(Gtk::Align::CENTER);
    //menuProfileBox.set_size_request(240, 64);
    //Glib::ustring temporaryTemmie = "temmie";
    menuProfileBox.set_username(username);
    // Attach: spacer row, then battleFrame, then buttonBox (Top -> Bot)
    screenGrid.attach(spacer,        0, 0); // blank space
    screenGrid.attach(barChartArea,  0, 1); // chart
    screenGrid.attach(battleFrame,   0, 2); // sits above buttons
    screenGrid.attach(menuProfileBox,0, 3);
    screenGrid.attach(buttonBox,     0, 4); // bottom row

    // puts box containing buttons onto screen
    set_child(screenGrid); 

    menuProfileBox.signal_upload().connect(
        sigc::mem_fun(*this, &mainScreen::on_pfpUpload_button_clicked)
    );

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
    currentChartKind = ChartKind::Bar;
    openBarMenu();
}

void mainScreen::on_pieChart_clicked(void) {
    currentChartKind = ChartKind::Pie;
    openPieMenu();
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

void mainScreen::openBarMenu(void){
    auto dialog = new Gtk::Dialog("Bar Chart Menu", *this);
    dialog->set_name("ut-box");
    
    dialog->set_modal(true);
    dialog->set_decorated(false);
    dialog->set_transient_for(*this);
    dialog->set_default_size(400, 280);

    auto content = dialog->get_content_area();
    content->set_orientation(Gtk::Orientation::VERTICAL);
    content->set_margin(20);
    content->set_spacing(8);

    auto label = Gtk::make_managed<Gtk::Label>("* What should the bar chart show?");
    label->set_halign(Gtk::Align::START);
    content->append(*label);

    // First button: group leader
    auto totalBtn = Gtk::make_managed<Gtk::CheckButton>("Total Percentage");
    totalBtn->set_active(true);
    content->append(*totalBtn);

    auto labBtn = Gtk::make_managed<Gtk::CheckButton>("Lab Percentage");
    labBtn->set_group(*totalBtn);
    content->append(*labBtn);

    auto quizBtn = Gtk::make_managed<Gtk::CheckButton>("Quiz Percentage");
    quizBtn->set_group(*totalBtn);
    content->append(*quizBtn);

    auto examBtn = Gtk::make_managed<Gtk::CheckButton>("Exam Percentage");
    examBtn->set_group(*totalBtn);
    content->append(*examBtn);

    auto projectBtn = Gtk::make_managed<Gtk::CheckButton>("Project Percentage");
    projectBtn->set_group(*totalBtn);
    content->append(*projectBtn);

    auto finalBtn = Gtk::make_managed<Gtk::CheckButton>("Final Percentage");
    finalBtn->set_group(*totalBtn);
    content->append(*finalBtn);

    // drop grades button use example
    auto gradeDropBtns = Gtk::make_managed<DropGradeBtn>();
    gradeDropBtns->setGradeDropped(userDropGrades);   // remember last choice
    content->append(*gradeDropBtns);

    dialog->add_button("_Cancel", Gtk::ResponseType::CANCEL);
    dialog->add_button("_OK",     Gtk::ResponseType::OK);

    dialog->signal_response().connect(
        sigc::bind(
            sigc::mem_fun(*this, &mainScreen::barMenuResponse),
            dialog,
            totalBtn, labBtn, quizBtn, examBtn, projectBtn, finalBtn,
            gradeDropBtns)
    );

    dialog->show();
}


void mainScreen::openPieMenu(void){
    auto dialog = new Gtk::Dialog("Pie Chart Options", *this);
    dialog->set_name("ut-box");

    dialog->set_modal(true);
    dialog->set_decorated(false);
    dialog->set_transient_for(*this);
    dialog->set_default_size(400, 200);

    auto content = dialog->get_content_area();
    content->set_orientation(Gtk::Orientation::VERTICAL);
    content->set_margin(20);
    content->set_spacing(8);

    auto gradeDropBtns = Gtk::make_managed<DropGradeBtn>();
    gradeDropBtns->setGradeDropped(userDropGrades);
    content->append(*gradeDropBtns);

    dialog->add_button("_Cancel", Gtk::ResponseType::CANCEL);
    dialog->add_button("_OK", Gtk::ResponseType::OK);

    dialog->signal_response().connect(
        sigc::bind(
            sigc::mem_fun(*this, &mainScreen::pieMenuResponse),
            dialog,
            gradeDropBtns
        )
    );

    dialog->show();
}

void mainScreen::openTextMenu(void) {
    // Create an Undertale-style dialog in the center
    auto dialog = new Gtk::Dialog("Text File Menu", *this);
    dialog -> set_name("ut-box");

    dialog -> set_modal(true);
    dialog -> set_decorated(false);           // no window frame = more "in-game"
    dialog -> set_default_size(960, 240);     // tweak for aesthetics

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

    // Hook response -> your handler
    dialog -> signal_response().connect(
        sigc::bind(
            sigc::mem_fun(*this, &mainScreen::textFileMenuResponse),
            dialog
        )
    );

    dialog -> show();
}

void mainScreen::openSortMenu(void) {
    auto dialog = new Gtk::Dialog("Sort Menu", *this);
    dialog->set_name("ut-box");
    
    dialog->set_modal(true);
    dialog->set_decorated(false);
    dialog->set_transient_for(*this);
    dialog->set_default_size(400, 280);

    auto content = dialog->get_content_area();
    content->set_orientation(Gtk::Orientation::VERTICAL);
    content->set_margin(20);
    content->set_spacing(8);

    auto label = Gtk::make_managed<Gtk::Label>("* How do you want to sort?");
    label->set_halign(Gtk::Align::START);
    content->append(*label);

    // First button: group leader
    auto studentID = Gtk::make_managed<Gtk::CheckButton>("Student ID");
    studentID->set_active(true);
    content->append(*studentID);

    auto letterGrade = Gtk::make_managed<Gtk::CheckButton>("Letter Grade");
    letterGrade->set_group(*studentID);
    content->append(*letterGrade);

    auto percentages = Gtk::make_managed<Gtk::CheckButton>("Percentages");
    percentages->set_group(*studentID);
    content->append(*percentages);

    // drop grades buttons (dropgradebtn) object
    auto gradeDropBtns = Gtk::make_managed<DropGradeBtn>();
    gradeDropBtns->setGradeDropped(userDropGrades);   // remember last choice
    content->append(*gradeDropBtns);

    dialog->add_button("_Cancel", Gtk::ResponseType::CANCEL);
    dialog->add_button("_OK",     Gtk::ResponseType::OK);

    dialog->signal_response().connect(
    sigc::bind(
        sigc::mem_fun(*this, &mainScreen::sortMenuResponse),
        dialog,
        studentID,
        letterGrade,
        percentages,
        gradeDropBtns
        )
    );

    dialog->show();
}
void mainScreen::fileChooserResponse(int response_id, Gtk::FileChooserDialog* dialog){
    if (response_id == Gtk::ResponseType::OK) {

        auto file = dialog->get_file();  // Gio::File
        if (file) {
            const std::string path = file->get_path();  // local filesystem path

            std::cout << "User selected file: " << path << "\n";

            // Basic validation: ensure .txt file
            if (path.size() < 4 || path.substr(path.size() - 4) != ".txt") {
                std::cerr << "Error: filename must end in .txt\n";
                battleText.set_text("Filename must end in .txt");
            }
            else {
                // Reuse your existing logic from filenameEntered()
                switch (userFileOption) {
                    case TextFileOption::ViewRaw: {
                        score.fileImportFromGTK(path);
                        if (score.checkFile()) {
                            battleText.set_text("* Viewing Raw Data");
                            viewRawText.set_transient_for(*this);
                            viewRawText.present();
                            viewRawText.setText(score.readRawData());
                        }
                        break;
                    }
                    case TextFileOption::Upload: {
                        score.fileImportFromGTK(path);
                        if (score.checkFile()) {
                            battleText.set_text("* File Uploaded");
                            score.countStudentsInFile();
                        }
                        break;
                    }
                    case TextFileOption::GenFile: {
                        randomScoreFile.generateReport(path);
                        battleText.set_text("Generated Random Score File");
                        break;
                    }
                }
            }
        }
    }

    // Bring main window back to front, same as other handlers
    this->present();

    delete dialog;
}


void mainScreen::sortMenuResponse(int response_id, Gtk::Dialog* dialog, 
    Gtk::CheckButton* studentID, Gtk::CheckButton* letterGrade, Gtk::CheckButton* percentages,
    DropGradeBtn* gradeDropBtns){
    if(response_id == Gtk::ResponseType::OK){
        if(studentID -> get_active()){
            userSortOption = SortByOption::StudentID;
            battleText.set_text("* Sort by StudentID");
            // set window title
            viewSortedResults.set_title("Sorted Results: StudentID");
        }
        else if (letterGrade -> get_active()){
            userSortOption = SortByOption::LetterGrade;
            battleText.set_text("* Sort by Letter Grade");
            viewSortedResults.set_title("Sorted Results: Letter Grade");
        }
        else if(percentages -> get_active()){
            userSortOption = SortByOption::TotalPerc;
            battleText.set_text("* Sort by Percentages");
            viewSortedResults.set_title("Sorted Results: Percentages");
        }
        userDropGrades = gradeDropBtns -> getGradeDropped();

        if (!score.checkFile()) {
            battleText.set_text("* Upload a file first!");
            this -> present();
            delete dialog;
            return;
        } else {
            // generate report
            score.generateReportClass(score.getClassSize(), /*sortSelect=*/static_cast<int>(userSortOption), /*isGradesDropped=*/ userDropGrades ? 1:0);
        }
        
        // open window to display file
        viewSortedResults.set_transient_for(*this);
        viewSortedResults.present();

        // ENTER FORMATTED DATA HERE
        viewSortedResults.setText(score.getClassReportString());
        // Make sure the main window comes back to the foreground
        this->present();
    }else{
        userSortOption = SortByOption::NoSort;
        battleText.set_text("* No Sort Selected");
    }

    delete dialog;
}

void mainScreen::textFileMenuResponse(int response_id, Gtk::Dialog* dialog) {
    switch (response_id) {
        case 1:
            std::cout << "Generate Random File\n";
            userFileOption = TextFileOption::GenFile;
            promptFilename();
            break;
        case 2:
            std::cout << "View Raw Text File\n";
            userFileOption = TextFileOption::ViewRaw;
            promptFilename();
            break;
        case 3:
            std::cout << "Upload File\n";
            userFileOption = TextFileOption::Upload;
            promptFilename();
            break;
        default:
            break; // Cancel or unknown
    }

    // Make sure the main window comes back to the foreground
    this->present();

    delete dialog; 
}

void mainScreen::drawBarChart(const Cairo::RefPtr<Cairo::Context>& cr, int width, int height){
    if (currentChartKind == ChartKind::Pie) {
        drawPieChart(cr, width, height);
        return;
    }

    cr->save();
    cr->set_source_rgb(0, 0, 0);
    cr->paint();
    cr->restore();

    if (barChartData.empty()) {
        draw_pango_text(cr, "No chart data.", 20, height / 2.0, 24, false);
        return;
    }

    double left = 60.0;
    double top = 40.0;
    double right = width - 40.0;
    double bottom = height - 80.0;

    double chartWidth = right - left;
    double chartHeight = bottom - top;

    cr->set_line_width(2.0);
    cr->set_source_rgb(1, 1, 1);

    cr->move_to(left, top);
    cr->line_to(left, bottom);
    cr->line_to(right, bottom);
    cr->stroke();

    double maxValue = 0.0;
    for (double v : barChartData) {
        if (v > maxValue) maxValue = v;
    }
    if (maxValue <= 0.0) 
        maxValue = 1.0;

    int n = barChartData.size();
    double barSpacing = 10.0;
    double barWidth = (chartWidth - (n + 1) * barSpacing) / n;

    for (int i = 0; i < n; ++i) {
        double value = barChartData[i];
        double barHeight = (value / maxValue) * chartHeight;

        double x = left + barSpacing + i * (barWidth + barSpacing);
        double y = bottom - barHeight;

        cr->set_source_rgb(1, 1,1);

        cr->rectangle(x, y, barWidth, barHeight);
        cr->fill();

        // Number label above bar (centered)
        std::string txt = std::to_string((int)(value * 100));
        double centerX = x + barWidth / 2.0;
        double textY = y - 18.0;
        draw_pango_text(cr, txt, centerX, textY, 18, true);
    }

    // Y-axis label rotated
    std::string yLabel = "Percentage";
    cr->save();
    cr->translate(left - 40.0, top + chartHeight / 2.0);
    cr->rotate(-G_PI / 2.0);
    draw_pango_text(cr, yLabel, 0.0, 0.0, 24, true);
    cr->restore();

    // X-axis label centered
    std::string xLabel = "Data Points";
    double cx = left + chartWidth / 2.0;
    double cy = bottom + 25.0;
    draw_pango_text(cr, xLabel, cx, cy, 24, true);

}
void mainScreen::drawPieChart(const Cairo::RefPtr<Cairo::Context>& cr, int width, int height){
    // Background
    cr->save();
    cr->set_source_rgb(0.0, 0.0, 0.0);
    cr->paint();
    cr->restore();

    // Basic sanity check
    if (pieChartData.size() < 5 || pieCounts.size() < 5 || pieTotalStudents <= 0) {
        draw_pango_text(cr, "No grade data.", 20, height / 2.0, 24, false);
        return;
    }

    // Center and radius
    const double cx = width  / 2.0;
    const double cy = height / 2.0;
    const double radius = std::min(width, height) * 0.35;

    // Sum of fractions (should be ~1.0, but we normalize anyway)
    double totalFraction = 0.0;
    for (double v : pieChartData) {
        totalFraction += v;
    }
    if (totalFraction <= 0.0) {
        draw_pango_text(cr, "No grade data.", 20, height / 2.0, 24, false);
        return;
    }

    double angle_start = 0.0;

    // Non-yellow palette (red, dark gold, bronze, green, blue)
    static const double colors[5][3] = {
        {1.0, 0.20, 0.20},   // A - red
        {1.0, 0.55, 0.15},   // B - dark gold
        {0.75, 0.55, 0.15},  // C - bronze
        {0.30, 0.80, 0.30},  // D - green
        {0.25, 0.35, 0.90}   // F - blue
    };

    // Grade labels for slices
    static const char gradeLetters[5] = { 'A', 'B', 'C', 'D', 'F' };

    for (int i = 0; i < 5; ++i) {
        const int count = (i < static_cast<int>(pieCounts.size()))
                          ? pieCounts[i]
                          : 0;
        if (count <= 0) {
            // No students with this grade; skip drawing a slice
            continue;
        }

        const double value = pieChartData[i];
        const double fraction = value / totalFraction;      // normalized 0–1
        const double angle_span = fraction * 2.0 * G_PI;
        const double angle_end = angle_start + angle_span;

        // Slice fill
        cr->set_source_rgb(colors[i][0], colors[i][1], colors[i][2]);
        cr->move_to(cx, cy);
        cr->arc(cx, cy, radius, angle_start, angle_end);
        cr->close_path();
        cr->fill();

        // Label position (center of the slice)
        const double mid_angle = angle_start + angle_span / 2.0;
        const double tx = cx + std::cos(mid_angle) * (radius * 0.65);
        const double ty = cy + std::sin(mid_angle) * (radius * 0.65);

        // Grade and label text
        const char grade = gradeLetters[i];
        const int percent = static_cast<int>(fraction * 100.0 + 0.5); // rounded %

        std::string label = std::string(1, grade) + " (" + std::to_string(count) + ", " + std::to_string(percent) + "%)";

        draw_pango_text(cr, label, tx, ty, 18, true);

        angle_start = angle_end;
    }

    // Caption text at bottom
    draw_pango_text(cr, "* Grade distribution (A-F)", 20, height - 30, 16, false);
}



void mainScreen::computePieFromCalcScore() {
    pieCounts.assign(5, 0);   // A,B,C,D,F
    pieChartData.clear();
    pieTotalStudents = 0;

    const auto& perc = score.getClassPercentages();
    if (perc.empty())
        return;

    for (const auto& row : perc) {
        if (row.size() < 6) continue;

        // Use calcScore’s logic:
        std::string gradeStr = score.getLetterGradeSorted(row);
        if (gradeStr.empty()) continue;

        char g = gradeStr[0];
        switch (g) {
            case 'A': ++pieCounts[0]; break;
            case 'B': ++pieCounts[1]; break;
            case 'C': ++pieCounts[2]; break;
            case 'D': ++pieCounts[3]; break;
            default:  ++pieCounts[4]; break; // treat others as F
        }
    }

    for (int c : pieCounts) pieTotalStudents += c;
    if (pieTotalStudents == 0)
        return;

    pieChartData.resize(5); // populates vector
    for (int i = 0; i < 5; ++i) {
        pieChartData[i] = static_cast<double>(pieCounts[i]) / pieTotalStudents;
    }

}

void mainScreen::barMenuResponse(int response_id, Gtk::Dialog* dialog, Gtk::CheckButton* totalBtn, Gtk::CheckButton* labBtn,
                                 Gtk::CheckButton* quizBtn, Gtk::CheckButton* examBtn, Gtk::CheckButton* projectBtn,
                                 Gtk::CheckButton* finalBtn,  DropGradeBtn* gradeDropBtns){
    if (response_id == Gtk::ResponseType::OK) {

        // Figure out which option the user chose
        if (totalBtn->get_active())
            userBarChartOption = BarChartOption::TotalPercent;
        else if (labBtn->get_active())
            userBarChartOption = BarChartOption::LabPercent;
        else if (quizBtn->get_active())
            userBarChartOption = BarChartOption::QuizPercent;
        else if (examBtn->get_active())
            userBarChartOption = BarChartOption::ExamPercent;
        else if (projectBtn->get_active())
            userBarChartOption = BarChartOption::ProjectPercent;
        else if (finalBtn->get_active())
            userBarChartOption = BarChartOption::FinalPercent;

        // Drop grade?
        userDropGrades = gradeDropBtns->getGradeDropped(); // true or false

        if (!score.checkFile()) {
            battleText.set_text("* Upload a file first!");
            barChartData.clear();
        } else {
            // Recompute report so vectors are fresh
            score.generateReportClass(score.getClassSize(), /*sortSelect=*/0, /*isGradesDropped=*/ userDropGrades ? 1:0);

            barChartData.clear();

            const auto& perc = score.getClassPercentages();
            if (!perc.empty()) {
                for (const auto& row : perc) {
                    // row layout (after getTotalPercentage):
                    // [0]=lab, [1]=quiz, [2]=midterms, [3]=project,
                    // [4]=final, [5]=total
                    switch (userBarChartOption) {
                        case BarChartOption::TotalPercent:
                            if (row.size() > 5)
                                barChartData.push_back(row[5]); // weighted final percentage
                            break;

                        case BarChartOption::LabPercent:
                            if (row.size() > 0) {
                                double w = score.getGradeWeight(0); // labs weight (0.15, etc.)
                                if (w > 0.0)
                                    barChartData.push_back(row[0] / w); // raw lab %
                            }
                            break;

                        case BarChartOption::QuizPercent:
                            if (row.size() > 1) {
                                double w = score.getGradeWeight(1);
                                if (w > 0.0)
                                    barChartData.push_back(row[1] / w); // raw quiz %
                            }
                            break;

                        case BarChartOption::ExamPercent:
                            if (row.size() > 2) {
                                double w = score.getGradeWeight(2);
                                if (w > 0.0)
                                    barChartData.push_back(row[2] / w); // raw exam %
                            }
                            break;

                        case BarChartOption::ProjectPercent:
                            if (row.size() > 3) {
                                double w = score.getGradeWeight(3);
                                if (w > 0.0)
                                    barChartData.push_back(row[3] / w); // raw project %
                            }
                            break;

                        case BarChartOption::FinalPercent:
                            if (row.size() > 4) {
                                double w = score.getGradeWeight(4);
                                if (w > 0.0)
                                    barChartData.push_back(row[4] / w); // raw final-exam %
                            }
                            break;
                    }
                }
            }
        }

        barChartArea.queue_draw();
    }

    // Make sure the main window comes back to the foreground
    this->present();

    delete dialog;
}

void mainScreen::pieMenuResponse(int response_id, Gtk::Dialog* dialog, DropGradeBtn* gradeDropBtns){
    if (response_id == Gtk::ResponseType::OK) {

        if (!score.checkFile()) {
            battleText.set_text("* Upload a file first!");
            // Make sure the main window comes back to the foreground
            this->present();
            delete dialog;
            return;
        }

        // Read “drop grades?” choice
        userDropGrades = gradeDropBtns->getGradeDropped();

        // Recompute report with chosen drop setting
        score.generateReportClass(
            // default sort to nothing
            score.getClassSize(), /*sortSelect=*/0, /*isGradesDropped=*/ userDropGrades ? 1 : 0
        );

        // Build A/B/C/D/F fractions using existing calcScore logic
        computePieFromCalcScore();                   // uses getClassPercentages + getLetterGradeSorted 

        currentChartKind = ChartKind::Pie;
        battleText.set_text("* Drawing pie chart: grade distribution.");

        barChartArea.queue_draw();
    }
    // Make sure the main window comes back to the foreground
    this->present();
    delete dialog;
}


void mainScreen::promptFilename(void){
    // Create an OPEN file chooser dialog parented to this window.
    auto dialog = new Gtk::FileChooserDialog( *this, "* Choose a text file", Gtk::FileChooser::Action::OPEN);

    dialog->set_modal(true);
    dialog->set_transient_for(*this);

    // Buttons: Cancel / Open
    dialog->add_button("_Cancel", Gtk::ResponseType::CANCEL);
    dialog->add_button("_Open",   Gtk::ResponseType::OK);

    // Filter set tto *.txt default
    auto filter_text = Gtk::FileFilter::create();
    filter_text->set_name("Text files (*.txt)");
    filter_text->add_pattern("*.txt");
    dialog->add_filter(filter_text);


    // auto filter_all = Gtk::FileFilter::create();
    // filter_all->set_name("All files");
    // filter_all->add_pattern("*");
    // dialog->add_filter(filter_all);

    // Connect response handler
    dialog->signal_response().connect(
        sigc::bind(
            sigc::mem_fun(*this, &mainScreen::fileChooserResponse),
            dialog
        )
    );

    dialog->show();
}


void mainScreen::filenameEntered(int response_id, Gtk::Dialog* dialog, Gtk::Entry* entry){
    if (response_id == Gtk::ResponseType::OK){ // gtk::responsetype::ok is basically an enum!!
        std::string filename = entry->get_text();

        // basic validation
        if (filename.size() < 4 || filename.substr(filename.size() - 4) != ".txt"){
            std::cerr << "Error: filename must end in .txt\n";
            battleText.set_text("Filename must end in .txt");
        } else {
            std::cout << "User entered filename: " << filename << "\n";

            switch (userFileOption){
                case TextFileOption::ViewRaw: {
                    score.fileImportFromGTK(filename);
                    if (score.checkFile()){
                        battleText.set_text("* Viewing Raw Data");
                        viewRawText.set_transient_for(*this);
                        viewRawText.present();
                        viewRawText.setText(score.readRawData());
                    }
                    break;
                }
                case TextFileOption::Upload: {
                    score.fileImportFromGTK(filename);
                    if (score.checkFile()){
                        battleText.set_text("* File Uploaded");
                        score.countStudentsInFile();
                    }
                    break;
                }
                case TextFileOption::GenFile: {
                    randomScoreFile.generateReport(filename);
                    battleText.set_text("* Generated Random Score File");
                    break;
                }
            }
        }
    }

    // Make sure the main window comes back to the foreground
    this->present();

    delete dialog; // kill dialog (gtkmm4)
}


void mainScreen::on_pfpUpload_button_clicked(void){
    auto dialog = new Gtk::FileChooserDialog(
        *this,
        "Choose a image file",
        Gtk::FileChooser::Action::OPEN
    );
    std::cout<<"IM FILECHOOSER!\n";
    auto folder = Gio::File::create_for_path(std::filesystem::current_path().string());
    dialog->set_current_folder(folder);

    dialog->set_modal(true);
    dialog->set_transient_for(*this);

    // Buttons: Cancel / Open
    dialog->add_button("_Cancel", Gtk::ResponseType::CANCEL);
    dialog->add_button("_Open",   Gtk::ResponseType::OK);
    std::cout<<"IM Buttons!\n";
    //filter 
    auto filter_image = Gtk::FileFilter::create();
    filter_image->set_name("Image files PNG JPEG JPG");
    filter_image->add_pattern("*.png");
    filter_image->add_pattern("*.jpg");
    filter_image->add_pattern("*.jpeg");
    dialog->add_filter(filter_image);

    auto filter_all = Gtk::FileFilter::create();
    filter_all->set_name("All files");
    filter_all->add_pattern("*");
    dialog->add_filter(filter_all);
    std::cout<<"IM FILTERS!\n";

    dialog->show();

    dialog->signal_response().connect(
        sigc::bind(
            sigc::mem_fun(*this, &mainScreen::fileChooserImageResponse),
            dialog
        )
    );

    
}

void mainScreen::fileChooserImageResponse(int response_id, Gtk::FileChooserDialog* dialog){
    if (response_id == Gtk::ResponseType::OK) {

        auto file = dialog->get_file();
        if (file) {
            const std::string path = file->get_path();

            // === Enforce PNG/JPG/JPEG formats ===
            std::string ext;
            {
                auto p = std::filesystem::path(path);
                ext = p.extension().string();
                std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
            }

            // Pass image to profile box (scaling handled there)
            menuProfileBox.set_pfpImg(path);
        }
    }

    this->present();
    delete dialog;
}
