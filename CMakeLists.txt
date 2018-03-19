project(ImageReader)
cmake_minimum_required(VERSION 3.4)

set (CMAKE_CXX_STANDARD 11)

# include init file macro and cmake modules
include(${CMAKE_CURRENT_LIST_DIR}/cmake/init.cmake)

# option for enable GUI
option(BUILD_GUI "BUILD GUI using Qt5" OFF)

# Find Boost program_options and format
find_package(Boost REQUIRED COMPONENTS program_options)

# main package
add_subdirectory(ImageReaderLibraries)
if(BUILD_GUI)
    add_subdirectory(ImageReaderGUI)
endif()

# TODO
option(TestCase OFF "Enable Test Case")
if(${TestCase})
    add_subdirectory(test)
endif()
