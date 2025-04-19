//
// Created by nenci on 12/02/2025.
//
#include <gtest/gtest.h>
#include "../include/Cell.h"
#include "../include/Cell.cpp"

TEST(CellTest, DefaultConstructor){
    Cell cell;
    EXPECT_EQ(cell.getValue(), "");
    EXPECT_EQ(cell.getOperationId(), OperationId::NoOp);
}

TEST(CellTest, SetValue){
    Cell cell;
    cell.setValue("42");
    EXPECT_EQ(cell.getValue(), "42");
}

TEST(CellTest, SetOperation){
    Cell cell;
    cell.setOperation(OperationId::Sum);
    EXPECT_EQ(cell.getOperationId(), OperationId::Sum);
}