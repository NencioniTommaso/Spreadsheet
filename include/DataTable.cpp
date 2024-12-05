#include "DataTable.h"

DataTable::DataTable(int r, int c) : rows(r), columns(c)
{
    table.resize(r * c);
    for(int i = 0; i < r * c; i++)
        table[i] = std::unique_ptr<Cell>(new Cell());
}

void DataTable::changeCell(int r, int c, std::string value) const
{
    table[r*columns + c]->setValue(value);
}

void DataTable::setCellBehav(const wxGridCellCoords& holder, const wxGridCellCoordsArray& selectedCells, OperationId op) const
{
    int hrow = holder.GetRow(), hcol = holder.GetCol();

    table[hrow*columns + hcol]->setOperationId(op);
    table[hrow*columns + hcol]->clearWatchedCells();

    for (size_t i = 0; i < selectedCells.size(); i++){
        table[hrow*columns + hcol]->attach( table[selectedCells[i].GetRow()*columns + selectedCells[i].GetCol()].get() );
    }

    table[hrow*columns + hcol]->calcValue();
}

std::string DataTable::getCellValue(const wxGridCellCoords &c) const
{
    return table[c.GetRow()*columns + c.GetCol()]->getValue();
}

void DataTable::resetCellOperation(int r, int c) const
{
    table[r*columns + c]->setOperationId(OperationId::NoOp);
}
