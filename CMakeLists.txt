cmake_minimum_required(VERSION 3.1)

set(project_name cpp-web-bookmanager)

set(CMAKE_CXX_STANDARD 17)

project(${project_name})

add_library(${project_name}-lib 
  src/AppComponents.hpp
  src/dto/DTOs.hpp
  src/controller/MyController.hpp
  src/controller/MyController.cpp
  src/constants/LogFlag.hpp
  src/components/SwaggerComponent.hpp
)

target_include_directories(${project_name}-lib PUBLIC src)

## link libraries

find_package(oatpp 1.4.0 REQUIRED)
if(oatpp_FOUND)
  message(STATUS "Found oatpp version: ${oatpp_VERSION}")
else()
  message(FATAL_ERROR "Could not find oatpp")
endif()

find_package(oatpp-swagger  1.4.0 REQUIRED)
if(oatpp-swagger_FOUND)
  message(STATUS "Found oatpp-swagger version: ${oatpp-swagger_VERSION}")
else()
  message(FATAL_ERROR "Could not find oatpp-swagger")
endif()

find_package(oatpp-sqlite 1.4.0 REQUIRED)
if(oatpp-sqlite_FOUND)
  message(STATUS "Found oatpp-sqlite version: ${oatpp-sqlite_VERSION}")
else()
  message(FATAL_ERROR "Cound not find oatpp-sqlite")
endif()

target_link_libraries(${project_name}-lib
  PUBLIC oatpp::oatpp
  PUBLIC oatpp::oatpp-swagger
  PUBLIC oatpp::oatpp-sqlite
)

add_definitions(
  ## define path to swagger-ui static resources folder
  -DOATPP_SWAGGER_RES_PATH="${oatpp-swagger_INCLUDE_DIRS}/../bin/oatpp-swagger/res"

  ## SQLite database file
  -DDATABASE_FILE="${CMAKE_CURRENT_SOURCE_DIR}/db.sqlite"
  ## SQLite database test file
  -DTESTDATABASE_FILE="${CMAKE_CURRENT_SOURCE_DIR}/test-db.sqlite"

  ## Path to database migration scripts
  -DDATABASE_MIGRATIONS="${CMAKE_CURRENT_SOURCE_DIR}/sql"
)

if(CMAKE_SYSTEM_NAME MATCHES Linux)
  find_package(Threads REQUIRED)
  target_link_libraries(${project_name}-lib INTERFACE Threads::Threads ${CMAKE_DL_LIBS})
endif()

## build executable
add_executable(${project_name}-exe src/App.cpp)
target_link_libraries(${project_name}-exe ${project_name}-lib)
add_dependencies(${project_name}-exe ${project_name}-lib)

add_executable(${project_name}-test 
  test/tests.cpp
  test/MyControllerTest.cpp
  test/MyControllerTest.hpp
  test/app/MyApiTestClient.hpp
  test/app/TestComponent.hpp
)

target_link_libraries(${project_name}-test ${project_name}-lib)
add_dependencies(${project_name}-test ${project_name}-lib)

set_target_properties(${project_name}-lib ${project_name}-exe PROPERTIES
  CXX_STANDARD 17
  CXX_EXTENSIONS OFF
  CXX_STANDARD_REQUIRED ON
)

enable_testing()

add_test(project-tests ${project_name}-test)