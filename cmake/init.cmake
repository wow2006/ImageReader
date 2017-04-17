# APPEND module path
list(APPEND CMAKE_MODULE_PATH
    ${CMAKE_SOURCE_DIR}/cmake/modules/)

include(${CMAKE_SOURCE_DIR}/cmake/macro.cmake)
COMPILE()
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
