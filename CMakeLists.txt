cmake_minimum_required(VERSION 3.1)

set(project_name cpp-web-bookmanager)

set(CMAKE_CXX_STANDARD 11)

project(${project_name})

add_library(${project_name}-lib src/AppComponents.hpp)

## link libraries
find_package(oatpp 1.3.0 REQUIRED)
target_link_libraries(${project_name}-lib
    PUBLIC oatpp::oatpp
    PUBLIC oatpp::oatpp-test
)

target_include_directories(${project_name}-lib PUBLIC src)

## build executable
add_executable(${project_name}-exe src/App.cpp)
target_link_libraries(${project_name}-exe ${project_name}-lib)
add_dependencies(${project_name}-exe ${project_name}-lib)

set_target_properties(${project_name}-lib ${project_name}-exe PROPERTIES
    CXX_STANDARD 17
    CXX_EXTENSIONS OFF
    CXX_STANDARD_REQUIRED ON
)