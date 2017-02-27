project(ImageReader)
cmake_minimum_required(VERSION 3.4)

find_package(Boost REQUIRED COMPONENTS program_options)
if (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
  add_definitions("/W2")
elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
  add_definitions("-Wall -std=c++14")
elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_definitions("-Wall -std=c++14 -fcolor-diagnostics")
endif()

add_subdirectory(ImageReaderLibraries)
add_subdirectory(ImageReaderGUI)

# TODO
option(TestCase OFF "Enable Test Case")
if(${TestCase})
    add_subdirectory(test)
endif()
