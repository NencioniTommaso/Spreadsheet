#ifndef SPREADSHEET_MYGRID_H
#define SPREADSHEET_MYGRID_H

#include <list>
#include <memory>
#include <wx/wx.h>
#include <wx/grid.h>
#include "DataTable.h"
#include "CellInputDialog.h"
#include "OperationId.h"

class MyGrid: public wxGrid{
public:
    MyGrid(wxWindow *parent, wxWindowID id, const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize,
             long style=wxWANTS_CHARS, const wxString &name=wxGridNameStr) : wxGrid(parent, id, pos, size, style, name) {}

    void setTable(int r, int c);
    void loadTable();

    void setLabels();

    void OnCellChange(const wxGridEvent& event);
    void OnCellRightClick(wxGridEvent& event);
    void OnPopUpClick(wxCommandEvent& event);

private:
    unsigned short int maxCol {26};
    std::unique_ptr<DataTable> dataTable;
};

#endif