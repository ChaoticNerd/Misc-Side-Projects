#include "profile.h"
#include <iostream>


profileBox::profileBox():
Gtk::Box(Gtk::Orientation::HORIZONTAL),
pfpUpload("Upload Image")
{

    set_spacing(10);
    set_margin(5);

    // Automatically adjust button box
    set_hexpand(true);
    set_vexpand(false);
    set_halign(Gtk::Align::FILL); // stretches horizontally
    set_valign(Gtk::Align::END); // puts at bottom of screen
    set_homogeneous(false); // all buttons same width

    

    user.set_margin_top(10);
    user.set_halign(Gtk::Align::CENTER);
    pfpUpload.get_style_context()->add_class("profile-Button");
    pfpImg.get_style_context()->add_class("avatar");
    const Glib::ustring& pfpPath = "assets/avatars/defaultPFP01.png";

    auto imgFile = Gio::File::create_for_path(pfpPath);
    pfpImg.set_file(imgFile);
    //pfpImg.set_pixel_size(32);
    pfpImg.set_can_shrink(true);
    pfpImg.set_content_fit(Gtk::ContentFit::SCALE_DOWN);
    pfpImg.set_halign(Gtk::Align::CENTER);
    pfpImg.set_valign(Gtk::Align::CENTER);
    pfpUpload.set_size_request(16,16);

    //pfpUpload.get_style_context()->add_class("profile-Button");
    pfpUpload.set_child(pfpImg);
    pfpUpload.set_size_request(16,16);
    append(user);
    append(pfpUpload);

    pfpUpload.signal_clicked().connect(sigc::mem_fun(
        *this, &profileBox::on_pfpUpload_button_clicked));

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
    std::cout<<"IM EMITTING MEPMEPMEP!\n";
    m_signal_upload.emit();
}