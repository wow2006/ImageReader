project(ImageReader)
cmake_minimum_required(VERSION 3.4)

if (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
  add_definitions("/W2")
elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
  add_definitions("-Wall -std=c++14")
endif()

add_subdirectory(ImageReaderLibraries)
add_subdirectory(ImageReaderGUI)

# TODO
option(TestCase OFF "Enable Test Case")
if(${TestCase})
    add_subdirectory(test)
endif()
