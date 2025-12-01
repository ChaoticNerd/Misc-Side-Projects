#include "mainScreen.h"
#include "calcScores.h"
#include <cairomm/cairomm.h>

// 0.9253 0.8647 0.9560 0.8190 0.8730 0.9263 0.7910 0.8750 0.8115 0.9775

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
    buttonBox.set_vexpand(false);
    buttonBox.set_halign(Gtk::Align::FILL); // stretches horizontally
    buttonBox.set_valign(Gtk::Align::END); // puts at bottom of screen
    buttonBox.set_homogeneous(true); // all buttons same width

    // Bar chart stuff
    barChartArea.set_vexpand(true);   // chart can grow vertically
    barChartArea.set_hexpand(true);   // chart stretches horizontally
    
    // button 1 (text file)
    textFile.add_css_class("Text-Button"); //reference to stly.css to do the orange and yellow buttons
    
    //textFile.set_label("Text File");
    textFile.set_hexpand(true);
    textFile.set_vexpand(true);
    textFile.set_size_request(240, 92);
    textFile.signal_clicked().connect(sigc::mem_fun(*this, &mainScreen::on_textFile_clicked));
    textFile.get_style_context()->add_class("Test-Button"); //reference to stly.css to do the orange and yellow buttons
    
    // button 2 (bar chart)
    barChart.add_css_class("Bar-Button"); //reference to stly.css to do the orange and yellow buttons
    //barChart.set_label("Bar Chart");
    barChart.set_hexpand(true);
    barChart.set_vexpand(true);
    barChart.set_size_request(240, 92);
    barChart.signal_clicked().connect(sigc::mem_fun(*this, &mainScreen::on_barChart_clicked));
    
    // button 3 (pie chart)
    pieChart.add_css_class("Pie-Button"); //reference to stly.css to do the orange and yellow buttons
    //pieChart.set_label("Pie Chart");
    pieChart.set_hexpand(true);
    pieChart.set_vexpand(true);
    pieChart.set_size_request(240, 92);
    pieChart.signal_clicked().connect(sigc::mem_fun(*this, &mainScreen::on_pieChart_clicked));

    // button 4 (sort) -- leads to drop-down menu type of thing
    sortBy.add_css_class("Sort-Button"); //reference to stly.css to do the orange and yellow buttons
    //sortBy.set_label("Sort by:");
    sortBy.set_hexpand(true);
    sortBy.set_vexpand(true);
    sortBy.set_size_request(240, 92);
    sortBy.signal_clicked().connect(sigc::mem_fun(*this, &mainScreen::on_sortBy_clicked));

    // Connect draw function
    barChartArea.set_draw_func(sigc::mem_fun(*this, &mainScreen::on_barChart_draw));

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

    

    // Attach: spacer row, then battleFrame, then buttonBox (Top -> Bot)
    screenGrid.attach(spacer,        0, 0); // blank space
    screenGrid.attach(barChartArea,  0, 1); // chart
    screenGrid.attach(battleFrame,   0, 2); // sits above buttons
    screenGrid.attach(buttonBox,     0, 3); // bottom row

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
    openBarMenu();
    // generateReportClass(userSortOption, int isGradesDropped);
}

void mainScreen::on_pieChart_clicked(void) {
    // TODO: use score to compute data and show a pie chart window
    std::cout << "Pie chart button clicked.\n";
    // generateReportClass(userSortOption, int isGradesDropped);

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

    // Divider
    auto sepLabel = Gtk::make_managed<Gtk::Label>("* Drop lowest scores?");
    sepLabel->set_margin_top(10);
    sepLabel->set_halign(Gtk::Align::START);
    content->append(*sepLabel);

    // --- Drop grades radio group ---
    auto dropNoBtn = Gtk::make_managed<Gtk::CheckButton>("No (use raw scores)");
    dropNoBtn->set_active(true);
    content->append(*dropNoBtn);

    auto dropYesBtn = Gtk::make_managed<Gtk::CheckButton>("Yes (apply drops)");
    dropYesBtn->set_group(*dropNoBtn);
    content->append(*dropYesBtn);

    dialog->add_button("_Cancel", Gtk::ResponseType::CANCEL);
    dialog->add_button("_OK",     Gtk::ResponseType::OK);

    dialog->signal_response().connect(
        sigc::bind(
            sigc::mem_fun(*this, &mainScreen::barMenuResponse),
            dialog,
            totalBtn, labBtn, quizBtn, examBtn, projectBtn, finalBtn,
            dropYesBtn)
    );

    dialog->show();
}


void mainScreen::openPieMenu(void){

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
    dialog -> set_default_size(960, 240);     // tweak for aesthetics

    // Content area acts like the white text box
    auto content = dialog -> get_content_area();
    content -> set_orientation(Gtk::Orientation::VERTICAL);
    content -> set_margin(20);

    auto label = Gtk::make_managed<Gtk::Label>("* How do you want to sort?");
    label -> set_halign(Gtk::Align::START);
    content -> append(*label);
    
    //Buttons act like the Undertale menu options
    //Justin added to make it more customizatble:
    auto battleGrid = Gtk::make_managed<Gtk::Grid>(); //grid layout within dialog
    content -> append(*battleGrid);  //attaching the new button grid to content
    battleGrid -> set_halign(Gtk::Align::FILL); //Makes sure the button layout is like the inventroy
    
    battleGrid -> set_column_spacing(5);     //Column is spacing for battleGrid
    battleGrid -> set_row_spacing(5);        //RowSpacing for battleGrid 
    battleGrid -> set_margin(5);             //Setting margins for battleGrid


    battleGrid -> set_hexpand(true);     //Expands horizontally
    battleGrid -> set_vexpand(false);    //but doesnt expands vertically

    
    auto btnStudentID   = Gtk::make_managed<Gtk::Button>("Student-ID");  //manually creating the buttons  so that i can customize more
    auto btnLetterGrade = Gtk::make_managed<Gtk::Button>("Letter-Grade");
    auto btnPercentage  = Gtk::make_managed<Gtk::Button>("Percentage");

    // not this, this is tasha:
    // dialog -> add_button("Student ID",   1);
    // dialog -> add_button("Letter Grade", 2);
    // dialog -> add_button("Percentage",   3);
    // not this, this is tasha
    
    
    battleGrid -> attach(*btnStudentID,    0, 0, 1, 1); // Button layout within the new BattleGrid
    battleGrid -> attach(*btnLetterGrade,  0, 1, 1, 1); //
    battleGrid -> attach(*btnPercentage,   1, 0, 1, 1); // 
    
    btnStudentID    -> set_hexpand(true);    //Expands Buttons to fit
    btnLetterGrade  -> set_hexpand(true);
    btnPercentage   -> set_hexpand(true);

    btnStudentID    -> signal_clicked().connect(sigc::bind([dialog]() { dialog->response(1);})); //
    btnLetterGrade  -> signal_clicked().connect(sigc::bind([dialog]() { dialog->response(2);}));
    btnPercentage   -> signal_clicked().connect(sigc::bind([dialog]() { dialog->response(3);}));
    
    //there was an attempt to make it match the layout but no...
    // screenGrid.attach(spacer,0, 0);
    // screenGrid.attach(*dialog, 0, 1);
    // screenGrid.attach(buttonBox,0, 2);
    //

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
            userSortOption = SortByOption::StudentID;
            //set text box to sort by student ID
            battleText.set_text("* Sort by StudentID");
            break;
        case 2:
            std::cout << "Sort by Letter Grade\n";
            userSortOption = SortByOption::LetterGrade;
            battleText.set_text("* Sort by Letter Grade");
            break;
        case 3:
            std::cout << "Sort by Percentage\n";
            userSortOption = SortByOption::TotalPerc;
            battleText.set_text("* Sort by Total Percent");
            break;
        default:
            userSortOption = SortByOption::NoSort;
            break; // Cancel or unknown
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

    delete dialog; 
}

void mainScreen::on_barChart_draw(const Cairo::RefPtr<Cairo::Context>& cr, int width, int height){
    // Background (black)
    cr->save();
    cr->set_source_rgb(0.0, 0.0, 0.0);
    cr->rectangle(0, 0, width, height);
    cr->fill();
    cr->restore();

    if (barChartData.empty()) {
        // nothing to draw yet
        cr->save();
        cr->set_source_rgb(1.0, 1.0, 1.0);
        cr->select_font_face("Determination Mono", Cairo::ToyFontFace::Slant::NORMAL, Cairo::ToyFontFace::Weight::NORMAL);
        cr->set_font_size(24.0);
        cr->move_to(20, height / 2);
        cr->show_text("No chart data.");
        cr->restore();
        return;
    }

    // Margins around chart area
    const double left   = 60.0;
    const double right  = 20.0;
    const double top    = 20.0;
    const double bottom = 50.0;   // a little extra for X label

    const double chartWidth  = width  - left - right;
    const double chartHeight = height - top  - bottom;

    if (chartWidth <= 0 || chartHeight <= 0)
        return;

    // Find max value for scaling
    double maxVal = 0.0;
    for (double v : barChartData)
        if (v > maxVal) maxVal = v;
    if (maxVal <= 0.0) maxVal = 1.0;

    // Axes
    cr->save();
    cr->set_source_rgb(1.0, 1.0, 1.0);
    cr->set_line_width(2.0);

    // Y axis
    cr->move_to(left, top);
    cr->line_to(left, top + chartHeight);

    // X axis
    cr->line_to(left + chartWidth, top + chartHeight);
    cr->stroke();
    cr->restore();

    // Bars
    const size_t n = barChartData.size();
    const double barSpace = chartWidth / static_cast<double>(n);
    const double barWidth = barSpace * 0.6;

    for (size_t i = 0; i < n; ++i) {
        double value = barChartData[i];
        double normalized = value / maxVal;   // e.g. 0.87

        double barHeight = normalized * chartHeight;
        double x = left + barSpace * i + (barSpace - barWidth) / 2.0;
        double y = top + chartHeight - barHeight;

        cr->save();
        cr->set_source_rgb(1.0, 1.0, 1.0);   // white bars
        cr->rectangle(x, y, barWidth, barHeight);
        cr->fill();
        cr->restore();
    }

    // =============================
    //  Axis labels (Cairo text)
    // =============================
    cr->save();
    cr->set_source_rgb(1.0, 1.0, 1.0);
    cr->select_font_face("Determination Mono", Cairo::ToyFontFace::Slant::NORMAL, Cairo::ToyFontFace::Weight::NORMAL);
    cr->set_font_size(24.0);

    Cairo::TextExtents ext;

    // Y-axis label ("Percentage")
    std::string yLabel = "Percentage";
    cr->get_text_extents(yLabel, ext);

    cr->save();
    // Put origin roughly in the middle of the y-axis
    cr->translate(left - 40.0, top + chartHeight / 2.0);
    cr->rotate(-G_PI / 2.0);  // vertical text
    // center text at (0,0) after rotation
    cr->move_to(-ext.width / 2.0 - ext.x_bearing,
                -ext.height / 2.0 - ext.y_bearing);
    cr->show_text(yLabel);
    cr->restore();

    // X-axis label depends on what user picked
    std::string xLabel;
    switch (userBarChartOption) {
        case BarChartOption::TotalPercent:   xLabel = "Total % per Student"; break;
        case BarChartOption::LabPercent:     xLabel = "Lab % per Student";   break;
        case BarChartOption::QuizPercent:    xLabel = "Quiz % per Student";  break;
        case BarChartOption::ExamPercent:    xLabel = "Exam % per Student";  break;
        case BarChartOption::ProjectPercent: xLabel = "Project % per Student"; break;
        case BarChartOption::FinalPercent:   xLabel = "Final % per Student"; break;
    }

    cr->get_text_extents(xLabel, ext);
    cr->move_to(left + chartWidth / 2.0 - (ext.width / 2.0 + ext.x_bearing),
                top + chartHeight + 35.0);
    cr->show_text(xLabel);

    cr->restore();

    // ======================================
    //  Numeric labels above each bar
    //  (only if there is enough horizontal space)
    // ======================================
    if (barSpace >= 10.0) {   // avoid ugly overlapping when too cramped
        cr->save();
        cr->set_source_rgb(1.0, 1.0, 1.0);
        cr->select_font_face("Determination Mono", Cairo::ToyFontFace::Slant::NORMAL, Cairo::ToyFontFace::Weight::NORMAL);
        cr->set_font_size(24.0);

        for (size_t i = 0; i < n; ++i) {
            double value = barChartData[i];
            if (value <= 0.0) continue;

            double normalized = value / maxVal;
            double barHeight  = normalized * chartHeight;
            double x = left + barSpace * i + (barSpace - barWidth) / 2.0;
            double y = top + chartHeight - barHeight;

            // Format as integer percentage (e.g. 87)
            int pctInt = static_cast<int>(value * 100.0 + 0.5);
            std::string txt = std::to_string(pctInt);

            Cairo::TextExtents textExt;
            cr->get_text_extents(txt, textExt);

            double textX = x + barWidth / 2.0
                         - (textExt.width / 2.0 + textExt.x_bearing);
            double textY = y - 3.0; // a little above the top of bar

            // Clamp so it doesn't go above the top margin
            if (textY - textExt.height < top)
                textY = top + textExt.height;

            cr->move_to(textX, textY);
            cr->show_text(txt);
        }

        cr->restore();
    }
}

void mainScreen::barMenuResponse(int response_id, Gtk::Dialog* dialog, Gtk::CheckButton* totalBtn, Gtk::CheckButton* labBtn,
                                 Gtk::CheckButton* quizBtn, Gtk::CheckButton* examBtn, Gtk::CheckButton* projectBtn,
                                 Gtk::CheckButton* finalBtn,  Gtk::CheckButton* dropYesBtn){
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
        userDropGrades = dropYesBtn->get_active(); // true or false

        if (!score.checkFile()) {
            battleText.set_text("* Upload a file first!");
            barChartData.clear();
        } else {
            // Recompute report so vectors are fresh
            score.generateReportClass(score.getClassSize(),
                                      /*sortSelect=*/0,     // sort by total %
                                      /*isGradesDropped=*/ userDropGrades ? 1:0);

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

            // Optional: debug print
            std::cout << "barChartData size: " << barChartData.size() << "\n";
            for (double v : barChartData)
                std::cout << v << " ";
            std::cout << std::endl;
        }

        barChartArea.queue_draw();
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
    dialog->set_default_size(960, 240);  // tweak as you like

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
            switch(userFileOption){
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
                    if(score.checkFile()){
                        battleText.set_text("* File Uploaded");
                        score.countStudentsInFile();
                    }
                    break;
                }
                case TextFileOption::GenFile:{ // maybe have this write to a file?
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

