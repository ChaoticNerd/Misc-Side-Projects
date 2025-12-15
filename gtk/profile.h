/**
 * This C++ program defines the profileBox GUI widget used to display a username
 * and profile picture with an upload button. <--- Edit this line if needed
 * CECS 275 - Fall 2021
 * @author Justin Narciso
 * @author Natasha Kho
 * @version 1.0.0
 */

#ifndef PROFILE_H
#define PROFILE_H

#include <gtkmm.h>
#include <filesystem>
#include <gtkmm/picture.h>
#include <sigc++/sigc++.h>

/**
 * @class profileBox
 * @brief A widget that displays a username and a profile picture upload button.
 *
 * The profileBox is a horizontal Gtk::Box that contains:
 *   - A label showing the current username.
 *   - A button containing a profile picture (avatar), which can be clicked to
 *     trigger an upload action.
 *
 * External code can connect to the upload signal to handle opening a file
 * chooser or updating the profile picture.
 */
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
    const int PFP_SIZE = 100;
    Gtk::Label user;
    Gtk::Button pfpUpload;
    Gtk::Picture pfpImg;

    type_signal_upload m_signal_upload;

    void on_pfpUpload_button_clicked();
};

#endif // PROFILE_H
