project(ImageViewerLibraries)

find_package(ZLIB REQUIRED)
find_package(PNG REQUIRED)
find_package(TIFF REQUIRED)
find_package(JPEG REQUIRED)

include_directories("${CMAKE_CURRENT_LIST_DIR}/hdr/")

file(GLOB hdr "${CMAKE_CURRENT_LIST_DIR}/hdr/*.hpp")
file(GLOB src "${CMAKE_CURRENT_LIST_DIR}/src/*.cpp")

add_library(${PROJECT_NAME} STATIC ${hdr} ${src})
target_link_libraries(
    ${PROJECT_NAME}
    ${ZLIB_LIBRARIES}
    ${PNG_LIBRARIES}
    ${JPEG_LIBRARY}
    ${Boost_LIBRARIES}
    ${TIFF_LIBRARIES} tiffxx
    turbojpeg
)
target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/hdr/
)
