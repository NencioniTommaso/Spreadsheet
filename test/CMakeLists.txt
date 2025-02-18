cmake_minimum_required(VERSION 3.28)
project(Spreadsheet)

add_subdirectory(lib/googletest-main)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(TEST_SOURCE_FILES
        CellTest.cpp
        DataTableTest.cpp
        runAllTest.cpp
)

add_executable(Spreadsheet_Test ${TEST_SOURCE_FILES})

target_link_libraries(Spreadsheet_Test gtest gtest_main)