cmake_minimum_required(VERSION 3.1)
project(hello)

set(CMAKE_CXX_STANDARD 11)
# set(SOURCE_FILES main.cpp handler.h)
set(SOURCE 
src/App.cpp 
src/Service/BookService.cpp 
src/Model/Book.cpp
)
# 查询依赖
find_package(oatpp REQUIRED)

add_executable(${PROJECT_NAME} ${SOURCE})

# 将目标文件与库文件进行链接
target_link_libraries(${PROJECT_NAME} oatpp::oatpp)