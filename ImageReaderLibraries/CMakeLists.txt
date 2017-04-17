project(ImageViewerLibraries)

find_package(ZLIB      REQUIRED)
find_package(TurboJPEG REQUIRED)
find_package(png++     REQUIRED)
find_package(TIFFXX    REQUIRED)
#find_package(JPEG REQUIRED)

include_directories("${CMAKE_CURRENT_LIST_DIR}/hdr/")

file(GLOB hdr "${CMAKE_CURRENT_LIST_DIR}/hdr/*.hpp")
file(GLOB src "${CMAKE_CURRENT_LIST_DIR}/src/*.cpp")

add_library(${PROJECT_NAME} STATIC ${hdr} ${src})

target_link_libraries(
    ${PROJECT_NAME}
    ${ZLIB_LIBRARIES}
    ${png++_LIBRARIES}
    ${TurboJPEG_LIBRARIES}
    ${Boost_LIBRARIES}
    ${TIFFXX_LIBRARIES}
)

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/hdr/
)
