cmake_minimum_required(VERSION 3.22.1)
project(gridproject)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../output)

find_package(wxWidgets REQUIRED COMPONENTS core base)
include(${wxWidgets_USE_FILE})
include_directories(include/libs)

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

#add_subdirectory(tests)