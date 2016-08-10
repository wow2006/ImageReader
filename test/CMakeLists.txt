project(test_project)
enable_testing()

find_package(GTest REQUIRED)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(
    ${PROJECT_NAME}
    ${GTEST_BOTH_LIBRARIES}
)
add_test(AllTestsInFoo ${PROJECT_NAME})
