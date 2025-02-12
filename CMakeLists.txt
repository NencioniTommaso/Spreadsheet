cmake_minimum_required(VERSION 3.22.1)
project(gridproject)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../output)

find_package(wxWidgets REQUIRED COMPONENTS core base)
include(${wxWidgets_USE_FILE})

set(SOURCES
        main.cpp
        include/Cell.cpp
        include/Cell.h
        include/DataTable.cpp
        include/DataTable.h
        include/MyApp.h
        include/MyFrame.cpp
        include/MyFrame.h
        include/MyGrid.cpp
        include/MyGrid.h
        include/Observer.h
        include/OperationId.h
        include/Subject.h
        include/CellInputDialog.h
)

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})

# Add GoogleTest as a subdirectory
add_subdirectory(test/lib/googletest-main)

# Include the GoogleTest include directories
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# Add the test executable
add_executable(Spreadsheet_Test
        test/CellTest.cpp
        test/MyGridTest.cpp
        test/runAllTest.cpp
)

# Link GoogleTest and wxWidgets libraries to the test executable
target_link_libraries(Spreadsheet_Test gtest gtest_main ${wxWidgets_LIBRARIES})

# Enable testing
enable_testing()

# Add tests
add_test(NAME SprdTest COMMAND Spreadsheet_Test)