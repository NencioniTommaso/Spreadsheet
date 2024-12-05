#ifndef SPREADSHEET_MYFRAME_H
#define SPREADSHEET_MYFRAME_H

#include <wx/wx.h>
#include <wx/grid.h>
#include "Observer.h"
#include "MyGrid.h"

class MyFrame : public wxFrame{
public:
    MyFrame(const wxString& title);
    ~MyFrame(){delete grid;}
private:
    MyGrid* grid;   
};

#endif