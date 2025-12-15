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
    pfpImg.set_size_request(100,100);
    // Configure upload button to display the profile image
    pfpUpload.set_size_request(100, 100);
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
    try {
        // Load full image from disk
        auto pixbuf = Gdk::Pixbuf::create_from_file(pfpPath);
        int src_w = pixbuf->get_width();
        int src_h = pixbuf->get_height();

        if (src_w <= 0 || src_h <= 0) {
            throw std::runtime_error("Avatar image has invalid size");
        }

        // Compute scale factor to fit in PFP_SIZE x PFP_SIZE (no upscaling)
        double scale = std::min(
            static_cast<double>(PFP_SIZE) / src_w,
            static_cast<double>(PFP_SIZE) / src_h
        );
        if (scale > 1.0) {
            scale = 1.0; // do not blow up small icons
        }

        int dest_w = std::max(1, static_cast<int>(src_w * scale));
        int dest_h = std::max(1, static_cast<int>(src_h * scale));

        auto scaled = pixbuf->scale_simple(dest_w, dest_h, Gdk::InterpType::BILINEAR);
        auto texture = Gdk::Texture::create_for_pixbuf(scaled);

        // Put scaled texture into picture
        pfpImg.set_paintable(texture);
        pfpImg.set_can_shrink(true);
        pfpImg.set_content_fit(Gtk::ContentFit::CONTAIN);
        pfpImg.set_halign(Gtk::Align::CENTER);
        pfpImg.set_valign(Gtk::Align::CENTER);
        pfpImg.set_size_request(PFP_SIZE, PFP_SIZE);
    }
    catch (const Glib::Error& ex) {
        std::cerr << "Failed to load avatar: " << ex.what() << "\n";
        // Fallback: reload default avatar so it never "disappears"
        try {
            const Glib::ustring defaultPath = "assets/avatars/defaultPFP01.png";
            auto pixbuf = Gdk::Pixbuf::create_from_file(defaultPath);
            auto texture = Gdk::Texture::create_for_pixbuf(pixbuf);
            pfpImg.set_paintable(texture);
        }
        catch (...) {
            // Last resort: swallow, but avoid crashing in UI callback
        }
    }
}



void profileBox::set_username(const Glib::ustring& username){
    user.set_text(username);
}

void profileBox::on_pfpUpload_button_clicked(){
    // Notify listeners that a profile picture upload was requested
    m_signal_upload.emit();
}
