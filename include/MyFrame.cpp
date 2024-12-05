#include "MyFrame.h"
#include "MyGrid.h"

MyFrame::MyFrame(const wxString& title)
       : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(800, 600)) {
    grid = new MyGrid(this, wxID_ANY, wxPoint(0, 0), wxSize(800, 600));

    const int rows = 60;
    const int columns = 26;

    grid->CreateGrid(rows, columns);
    grid->setLabels();
    grid->setTable(rows, columns);
    grid->EnableEditing(true);

    grid->Bind(wxEVT_GRID_CELL_CHANGED, &MyGrid::OnCellChange, grid);
    grid->Bind(wxEVT_GRID_CELL_RIGHT_CLICK, &MyGrid::OnCellRightClick, grid);
}