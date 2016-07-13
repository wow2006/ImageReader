project(ImageViewerLibraries)

include_directories("${CMAKE_CURRENT_LIST_DIR}/hdr/")

file(GLOB hdr "${CMAKE_CURRENT_LIST_DIR}/hdr/*.hpp")
file(GLOB src "${CMAKE_CURRENT_LIST_DIR}/src/*.cpp")

add_library(${PROJECT_NAME} STATIC ${hdr} ${src})
#target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES} ${PNG_LIBRARIES} ${ZLIB_LIBRARIES})
