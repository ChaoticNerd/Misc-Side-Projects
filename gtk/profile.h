#ifndef PROFILE_H
#define PROFILE_H

#include <gtkmm.h>
#include <filesystem>
#include <gtkmm/picture.h>
#include <sigc++/sigc++.h>

class profileBox : public Gtk::Box {
public:
    using type_signal_upload = sigc::signal<void()>;
    
    profileBox();
    explicit profileBox(const Glib::ustring& username);

    Gtk::Button& get_pfpUpload();           
    type_signal_upload& signal_upload();  

    void set_username(const Glib::ustring& username);
    void set_pfpImg(const Glib::ustring& pfpPath);

private:
    Gtk::Label user;
    Gtk::Button pfpUpload;
    Gtk::Picture pfpImg;  


    type_signal_upload m_signal_upload;

 
    void on_pfpUpload_button_clicked();
};

#endif 
