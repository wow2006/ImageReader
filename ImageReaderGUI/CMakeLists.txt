project(GUI)

find_package(Qt5Widgets REQUIRED)
set(CMAKE_AUTOMOC ON)

include_directories(
    ${CMAKE_CURRENT_LIST_DIR}/hdr
    ${CMAKE_CURRENT_BINARY_DIR}
    ${Boost_INCLUDE_DIRS})

file(GLOB src "src/*.cpp")
file(GLOB hdr "hdr/*.h")
file(GLOB ui  "ui/*.ui")

QT5_WRAP_UI(UIS_HDRS
    ${ui}
)

add_executable(${PROJECT_NAME} ${src} ${hdr} ${UIS_HDRS})

qt5_use_modules(${PROJECT_NAME} Widgets)

target_link_libraries(${PROJECT_NAME}
    ${QT_LIBRARIES}
    ${Boost_LIBRARIES}
    ImageViewerLibraries)
add_custom_command(
    TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/bin
    COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_NAME} ${CMAKE_BINARY_DIR}/bin
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_LIST_DIR}/images/Lenna.png ${CMAKE_BINARY_DIR}/bin
)
