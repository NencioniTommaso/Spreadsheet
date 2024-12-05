#ifndef SPREADSHEET_MYAPP_H
#define SPREADSHEET_MYAPP_H

#include <wx/wx.h>
#include "MyFrame.h"

class MyApp : public wxApp {
public:
    virtual bool OnInit();
};

bool MyApp::OnInit() {
    MyFrame *frame = new MyFrame("Spreadsheet");
    //frame->Center();
    //frame->SetClientSize(1000, 600);
    frame->Show(true);
    return true;
}

#endif