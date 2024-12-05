#ifndef SPREADSHEET_DATATABLE_H
#define SPREADSHEET_DATATABLE_H

#include <memory>
#include <vector>
#include <wx/wx.h>
#include <wx/grid.h>
#include "Subject.h"
#include "Observer.h"
#include "Cell.h"

class DataTable{
public:
    explicit DataTable(int r = 0, int c = 0);
    ~DataTable() {table.clear();}

    void changeCell(int r, int c, std::string value) const;
    void setCellBehav(const wxGridCellCoords& holder, const wxGridCellCoordsArray& selectedCells, OperationId op) const;
    std::string getCellValue(const wxGridCellCoords& c) const;
    void resetCellOperation(int r, int c) const;

private:
    int rows, columns;
    std::vector<std::unique_ptr<Cell>> table;
};

#endif
