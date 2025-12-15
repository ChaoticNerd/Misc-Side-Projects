/**
 * This C++ program defines a window class for displaying large blocks of
 * read-only text inside a scrollable view, with ESC to close.
 *
 * CECS 275 - Fall 2025
 * @author Justin Narciso
 * @author Natasha Kho
 * @version 1.0.0
 */

#ifndef TEXTVIEWER_H
#define TEXTVIEWER_H

#include <gtkmm.h>

/**
 * @class textViewer
 * @brief A simple read-only text viewing window with scrollbars and ESC to close.
 *
 * The textViewer window is intended to show reports or other long text output
 * from the main application. It:
 *  - Displays text in a Gtk::TextView inside a Gtk::ScrolledWindow.
 *  - Is non-editable.
 *  - Closes when the user presses the Escape key.
 */
class textViewer : public Gtk::Window {
public:
    /**
     * @brief Constructs the text viewer window.
     *
     * Sets the default size, creates the text buffer, places the text view
     * inside a scrollable window, and installs a key controller to handle
     * the ESC key.
     */
    textViewer();

    /**
     * @brief Sets the text displayed in the viewer.
     *
     * @param text The new text content to display.
     */
    void setText(const std::string& text);

private:
    Gtk::ScrolledWindow scrolledWindow;      ///< Container providing scrollbars.
    Gtk::TextView textView;                  ///< Read-only text display widget.
    Glib::RefPtr<Gtk::TextBuffer> buffer;    ///< Backing text buffer for the view.

    Glib::RefPtr<Gtk::EventControllerKey> key_controller; ///< Handles key events.

    /**
     * @brief Key press handler for the window.
     *
     * Currently used to detect ESC (Escape) key presses and close the
     * window when pressed.
     *
     * @param keyval  The GDK key value (e.g., GDK_KEY_Escape).
     * @param keycode Hardware keycode (unused).
     * @param state   Modifier key state (Ctrl, Alt, etc.) (unused).
     * @return true if the event was handled, false otherwise.
     */
    bool on_key_pressed(guint keyval, guint /*keycode*/, Gdk::ModifierType /*state*/);
};

#endif // TEXTVIEWER_H
