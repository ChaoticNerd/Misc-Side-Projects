/**
 * This C++ program defines the profileBox GUI widget used to display a username
 * and profile picture with an upload button.
 * CECS 275 - Fall 2025
 * @author Justin Narciso
 * @author Natasha Kho
 * @version 1.0.0
 */

#include "profile.h"
#include <iostream>

profileBox::profileBox()
: Gtk::Box(Gtk::Orientation::HORIZONTAL),
  pfpUpload("Upload Image"){
    // Layout configuration
    set_spacing(10);
    set_margin(5);
    set_hexpand(true);             // stretch horizontally
    set_vexpand(false);            // keep compact vertically
    set_halign(Gtk::Align::FILL);
    set_valign(Gtk::Align::END);
    set_homogeneous(false);

    // Username label
    user.set_margin_top(10);
    user.set_halign(Gtk::Align::CENTER);

    // Styling for widgets
    pfpUpload.get_style_context()->add_class("profile-Button");
    pfpImg.get_style_context()->add_class("avatar");

    // Load default profile image
    const Glib::ustring& pfpPath = "assets/avatars/defaultPFP01.png";
    auto imgFile = Gio::File::create_for_path(pfpPath);

    pfpImg.set_file(imgFile);
    pfpImg.set_can_shrink(true);
    pfpImg.set_content_fit(Gtk::ContentFit::SCALE_DOWN);
    pfpImg.set_halign(Gtk::Align::CENTER);
    pfpImg.set_valign(Gtk::Align::CENTER);
    pfpImg.set_size_request(16,16);
    // Configure upload button to display the profile image
    pfpUpload.set_size_request(16, 16);
    pfpUpload.set_child(pfpImg);

    // Add widgets to the container
    append(user);
    append(pfpUpload);

    // Connect upload button signal
    pfpUpload.signal_clicked().connect(
        sigc::mem_fun(*this, &profileBox::on_pfpUpload_button_clicked)
    );
}

profileBox::profileBox(const Glib::ustring& username)
: profileBox(){
    set_username(username);
}

profileBox::type_signal_upload& profileBox::signal_upload(){
    return m_signal_upload;
}

Gtk::Button& profileBox::get_pfpUpload(){
    return pfpUpload;
}

void profileBox::set_pfpImg(const Glib::ustring& pfpPath){
    auto imgFile = Gio::File::create_for_path(pfpPath);
    pfpImg.set_file(imgFile);
}

void profileBox::set_username(const Glib::ustring& username){
    user.set_text(username);
}

void profileBox::on_pfpUpload_button_clicked(){
    // Notify listeners that a profile picture upload was requested
    m_signal_upload.emit();
}
