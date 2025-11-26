#include "loginWindow.h"
#include <iostream>
#include <fstream>
#include <string>

loginWindow::loginWindow(){
    set_title("Login Window");
    set_default_size(800, 600);
    
    screenGrid.set_halign(Gtk::Align::FILL);
    screenGrid.set_valign(Gtk::Align::FILL);

    screenGrid.set_margin(20);
    screenGrid.set_row_spacing(10);
    screenGrid.set_column_spacing(10);

    screenGrid.set_hexpand(true);
    screenGrid.set_vexpand(true);

    textBox.set_orientation(Gtk::Orientation::VERTICAL);
    textBox.set_spacing(10);
    textBox.set_margin(5);

    textBox.set_hexpand(true);
    textBox.set_vexpand(true);
    textBox.set_halign(Gtk::Align::FILL);
    textBox.set_valign(Gtk::Align::END);
    textBox.set_homogeneous(true);
    
    // username entry
    usernameEntry.set_placeholder_text("Username");
    usernameEntry.set_hexpand(true);
    usernameEntry.set_vexpand(true);
    usernameEntry.set_size_request(20, 20);

    // password entry
    passwordEntry.set_placeholder_text("Password");
    passwordEntry.set_hexpand(true);
    passwordEntry.set_vexpand(true);
    passwordEntry.set_size_request(20, 20);

    //login button
    loginButton.set_label("Login");
    loginButton.set_hexpand(true);
    loginButton.set_vexpand(true);
    loginButton.set_size_request(20, 20);


    
    textBox.append(usernameEntry);
    textBox.append(passwordEntry);
    textBox.append(loginButton);

    screenGrid.attach(textBox, 0, 300);

    set_child(screenGrid);

    // loginButton.signal_clicked().connect([this]() {
    //     // Handle login button click event
    //     auto username = usernameEntry.get_text();
    //     auto password = passwordEntry.get_text();
    //     // Add your login logic here
    // });
    loginButton.signal_clicked().connect(sigc::mem_fun(*this, &loginWindow::on_login_button_clicked));
}

void loginWindow::on_login_button_clicked(){
    std::string username = usernameEntry.get_text();
    std::string password = passwordEntry.get_text();
    std::cout << "Username: " << username << ", Password: " << password << std::endl;
    // Placeholder for login button click handling
}