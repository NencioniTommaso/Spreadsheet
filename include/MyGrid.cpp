#include "MyGrid.h"
#include <string>

#define ID_OP_MAX 2001
#define ID_OP_MIN 2002
#define ID_OP_MEAN 2003
#define ID_OP_SUM 2004

void MyGrid::setTable(int r, int c)
{
    dataTable = std::unique_ptr<DataTable>(new DataTable(r, c));
}

void MyGrid::loadTable()
{
    for(int i = 0; i < GetNumberRows(); i++){
        for(int j = 0; j < GetNumberCols(); j++)
            SetCellValue(i, j, wxString(dataTable->getCellValue(wxGridCellCoords(i, j))));
    }
}

void MyGrid::setLabels()
{
    const std::string colLabels[maxCol] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L",
                                    "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"};
    for(int i = 0; i < GetNumberCols(); i++)
        SetColLabelValue(i, colLabels[i]);
}

void MyGrid::OnCellChange(const wxGridEvent &event)
{
    dataTable->changeCell(event.GetRow(), event.GetCol(), std::string(GetCellValue(event.GetRow(), event.GetCol()).utf8_str().data()));
    dataTable->resetCellOperation(event.GetRow(), event.GetCol());
    loadTable();
}

void MyGrid::OnCellRightClick(wxGridEvent &event)
{
    wxMenu menu;
    menu.Append(ID_OP_MAX, "Max");
    menu.Append(ID_OP_MIN, "Min");
    menu.Append(ID_OP_MEAN, "Mean");
    menu.Append(ID_OP_SUM, "Sum");

    menu.Bind(wxEVT_COMMAND_MENU_SELECTED, &MyGrid::OnPopUpClick, this);
    PopupMenu(&menu);
}

void MyGrid::OnPopUpClick(wxCommandEvent &event)
{
    if(IsSelection()){
        wxGridCellCoordsArray selectedCells;

        wxGridCellCoordsArray selectedBlocks = GetSelectionBlockTopLeft();
        wxGridCellCoordsArray selectedBlockBottomRight = GetSelectionBlockBottomRight();

        for (size_t i = 0; i < selectedBlocks.GetCount(); i++) {
            wxGridCellCoords topLeft = selectedBlocks[i];
            wxGridCellCoords bottomRight = selectedBlockBottomRight[i];

            for (int r = topLeft.GetRow(); r <= bottomRight.GetRow(); r++) {
                for (int c = topLeft.GetCol(); c <= bottomRight.GetCol(); c++) {
                    selectedCells.Add(wxGridCellCoords(r, c));
                }
            }
        }

        CellInputDialog inputDialog(this);
        if (inputDialog.ShowModal() == wxID_OK) {
            int row = inputDialog.GetRow() - 1;
            int col = inputDialog.GetCol() - 1;

            if (row < 0 || col < 0 || row >= GetNumberRows() || col >= GetNumberCols()) {
                wxMessageBox("Invalid cell coordinates!", "Error", wxOK | wxICON_ERROR);
                return;
            }

            wxGridCellCoords holder(row, col);

            switch(event.GetId()){
                case ID_OP_MAX:
                    dataTable->setCellBehav(holder, selectedCells, OperationId::Max);
                    break;
                case ID_OP_MIN:
                    dataTable->setCellBehav(holder, selectedCells, OperationId::Min);
                    break;
                case ID_OP_MEAN:
                    dataTable->setCellBehav(holder, selectedCells, OperationId::Mean);
                    break;
                case ID_OP_SUM:
                    dataTable->setCellBehav(holder, selectedCells, OperationId::Sum);
                    break;
                default:
                    break;
            }

            const auto str = wxString(dataTable->getCellValue(holder));
            SetCellValue(holder.GetRow(), holder.GetCol(), str);
        }
    }  
}
