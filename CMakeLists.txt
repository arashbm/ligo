cmake_minimum_required(VERSION 3.12)

project(ligo LANGUAGES CXX VERSION 0.0.1)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_POSITION_INDEPENDENT_CODE True)

if (NOT TARGET Python::Module OR NOT TARGET Python::Interpreter)
  set(Python_FIND_FRAMEWORK LAST)
  find_package(Python 3.8 COMPONENTS Interpreter Development REQUIRED)
endif()

include(FetchContent)
FetchContent_Declare(
  fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt
  GIT_TAG 9.1.0)
FetchContent_Declare(
  metal
  GIT_REPOSITORY https://github.com/brunocodutra/metal.git
  GIT_TAG v2.1.4)

FetchContent_MakeAvailable(fmt metal)

SET(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_CLANG_TIDY
  clang-tidy;
  --config-file=${CMAKE_CURRENT_SOURCE_DIR}/.clang-tidy;
  --header-filter=${CMAKE_CURRENT_SOURCE_DIR}/include;
  --warnings-as-errors=*;)

add_library(${PROJECT_NAME} STATIC
  src/concrete_objects.cpp
  src/abstract_objects.cpp
  src/handle.cpp
  src/abstract_objects.cpp
  src/python_module.cpp
  src/python_types.cpp
  src/python_methods.cpp)
target_link_libraries(${PROJECT_NAME} PUBLIC fmt Metal)
target_include_directories(${PROJECT_NAME} PUBLIC include/)
target_include_directories(${PROJECT_NAME} PRIVATE ${Python_INCLUDE_DIRS})

add_subdirectory(tests)
