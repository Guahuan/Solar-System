cmake_minimum_required(VERSION 3.16)
project(SOLAR_SYSTEM)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_compile_options(-Wall -Wextra)

find_package(Eigen3 REQUIRED)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/src/test.cpp)
target_link_libraries(${PROJECT_NAME} PUBLIC Eigen3::Eigen GL GLU glut)
