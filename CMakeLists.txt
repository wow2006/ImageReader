project(ImageReader)
cmake_minimum_required(VERSION 3.4)

find_package(Boost COMPONENTS program_options REQUIRED)
find_package(ZLIB REQUIRED)
find_package(PNG REQUIRED)
find_package(TIFF REQUIRED)
find_package(JPEG REQUIRED)
find_package(GTest REQUIRED)

include_directories(${PNG_CPP_INCLUDE_DIRS} ${PNG_INCLUDE_DIRS} "ImageReaderLibraries/hdr")


if (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
  add_definitions("/W2")
elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
  add_definitions("-Wall -std=c++14")
endif()

include_directories(${Boost_INCLUDE_DIR})

add_subdirectory(ImageReaderLibraries)
add_subdirectory(ImageReaderGUI)


