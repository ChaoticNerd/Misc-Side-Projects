/**
 * This C++ program defines a GUI widget for selecting whether a grade is dropped
 * using a pair of Yes/No toggle buttons.
 * CECS 275 - Fall 2025
 * @author Justin Narciso
 * @author Natasha Kho
 * @version 1.0.0
 */

#ifndef DROP_GRADE_BTN_H
#define DROP_GRADE_BTN_H

#include <gtkmm.h>

/**
 * @class DropGradeBtn
 * @brief A small UI component that allows the user to indicate whether a grade
 *        should be dropped using two check buttons (Yes/No).
 *
 * The widget is a Gtk::Box containing:
 * - A label separator (e.g., ":")
 * - A "No" check button
 * - A "Yes" check button
 *
 * Only one button should be considered active at a time.  
 * The class stores the selected state and provides getters/setters for access.
 */
class DropGradeBtn : public Gtk::Box {
private:
    Gtk::Label sepLabel;            ///< Label used as a separator or descriptor.
    Gtk::CheckButton dropNoBtn;     ///< Button indicating the grade should NOT be dropped.
    Gtk::CheckButton dropYesBtn;    ///< Button indicating the grade SHOULD be dropped.

    bool isGradeDropped;            ///< True if user selected "Yes", false otherwise.

public:
    /**
     * @brief Constructs the grade-drop selection widget.
     *
     * Sets up the label and check buttons inside the box and initializes
     * internal state to default values.
     */
    DropGradeBtn(void);

    /**
     * @brief Returns whether the grade is considered dropped.
     * @return True if dropped, false if not.
     */
    bool getGradeDropped(void) const;

    /**
     * @brief Sets whether the grade is dropped.
     * @param in Boolean value representing the desired state.
     */
    void setGradeDropped(bool in);
};

#endif // DROP_GRADE_BTN_H
