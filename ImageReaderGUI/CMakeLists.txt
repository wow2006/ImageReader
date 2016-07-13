project(GUI)

find_package(Qt5Widgets REQUIRED)
set(CMAKE_AUTOMOC ON)

include_directories(${CMAKE_CURRENT_LIST_DIR}/hdr ${CMAKE_CURRENT_BINARY_DIR})

file(GLOB src "src/*.cpp")
file(GLOB hdr "hdr/*.h")
file(GLOB ui  "ui/*.ui")
QT5_WRAP_UI(UIS_HDRS
    ${ui}
)

message(${CMAKE_CURRENT_BINARY_DIR}/../ImageReaderLibraries/)

add_executable(${PROJECT_NAME} ${src} ${hdr} ${UIS_HDRS})
qt5_use_modules(${PROJECT_NAME} Widgets)
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES}
    ${PNG_LIBRARIES} ${ZLIB_LIBRARIES} ${QT_LIBRARIES}
    "${CMAKE_CURRENT_BINARY_DIR}/../ImageReaderLibraries/libImageViewerLibraries.a")
