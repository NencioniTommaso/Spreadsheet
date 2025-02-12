//
// Created by nenci on 12/02/2025.
//
#include <gtest/gtest.h>
#include "../include/Cell.h"
#include "../include/Cell.cpp"

TEST(CellTest, DefaultConstructor)
{
    Cell cell;
    EXPECT_EQ(cell.getValue(), "");
    EXPECT_EQ(cell.getOperationId(), OperationId::NoOp);
}

TEST(CellTest, SetValue)
{
    Cell cell;
    cell.setValue("42");
    EXPECT_EQ(cell.getValue(), "42");
}

TEST(CellTest, SetOperationId)
{
    Cell cell;
    cell.setOperationId(OperationId::Sum);
    EXPECT_EQ(cell.getOperationId(), OperationId::Sum);
}

TEST(CellTest, CalculationOperations)
{
    Cell cell1, cell2, cell3;
    cell1.setValue("10");
    cell2.setValue("20");
    cell3.setValue("30");

    Cell resultCell;
    resultCell.attach(&cell1);
    resultCell.attach(&cell2);
    resultCell.attach(&cell3);
    resultCell.setOperationId(OperationId::Sum);
    resultCell.calcValue();

    EXPECT_EQ(resultCell.getValue(), "60.000000");
}