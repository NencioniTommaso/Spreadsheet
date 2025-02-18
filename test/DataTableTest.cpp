//
// Created by nenci on 17/02/2025.
//
#include <gtest/gtest.h>
#include <memory>
#include "../include/DataTable.h"
#include "../include/DataTable.cpp"

class DataTableTest : public ::testing::Test{
protected:
    void SetUp() override {
        dataTable = std::unique_ptr<DataTable>(new DataTable(3, 3));

        dataTable->changeCell(0, 0, "10");
        dataTable->changeCell(0, 1, "20");
        dataTable->changeCell(0, 2, "30");

        selectedCells.Add(wxGridCellCoords(0, 0));
        selectedCells.Add(wxGridCellCoords(0, 1));
        selectedCells.Add(wxGridCellCoords(0, 2));

        holder.Set(1, 1);
    }

    std::unique_ptr<DataTable> dataTable;
    wxGridCellCoordsArray selectedCells;
    wxGridCellCoords holder;
};

TEST_F(DataTableTest, ChangeCell){
    dataTable->changeCell(0, 0, "A1");

    EXPECT_EQ(dataTable->getCellValue(wxGridCellCoords(0, 0)), "A1");
}

TEST_F(DataTableTest, SetCellBehavSumOperation){
    dataTable->setCellBehav(holder, selectedCells, OperationId::Sum);
    EXPECT_EQ(dataTable->getCellValue(holder), "60.000000");
}

TEST_F(DataTableTest, SetCellBehavMeanOperation) {
    dataTable->setCellBehav(holder, selectedCells, OperationId::Mean);
    EXPECT_EQ(dataTable->getCellValue(holder), "20.000000");
}

TEST_F(DataTableTest, SetCellBehavMaxOperation) {
    dataTable->setCellBehav(holder, selectedCells, OperationId::Max);
    EXPECT_EQ(dataTable->getCellValue(holder), "30.000000");
}

TEST_F(DataTableTest, SetCellBehavMinOperation) {
    dataTable->setCellBehav(holder, selectedCells, OperationId::Min);
    EXPECT_EQ(dataTable->getCellValue(holder), "10.000000");
}