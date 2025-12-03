#ifndef DROP_GRADE_BTN_H
#define DROP_GRADE_BTN_H
#include <gtkmm.h>

class DropGradeBtn : public Gtk::Box{
    private:
        Gtk::Label sepLabel;
        Gtk::CheckButton dropNoBtn, dropYesBtn;
        // Gtk::Separator separatorLine;
        
        bool isGradeDropped;
    public:
        DropGradeBtn(void);
        bool getGradeDropped(void) const;
        void setGradeDropped(bool in);

};

#endif