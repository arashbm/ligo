cmake_minimum_required(VERSION 3.12)

project(ligo LANGUAGES CXX VERSION 0.0.1)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_POSITION_INDEPENDENT_CODE True)

option(LIGO_TIDY "Run clang-tidy with the build" OFF)

if (NOT TARGET Python::Module OR NOT TARGET Python::Interpreter)
  set(Python_FIND_FRAMEWORK LAST)

  if (WIN32 AND CMAKE_VERSION VERSION_GREATER_EQUAL 3.26 AND Python_INTERPRETER_ID STREQUAL "Python")
    find_package(Python 3.8 COMPONENTS Interpreter Development.Module REQUIRED)
  else()
    find_package(Python 3.8 COMPONENTS Interpreter Development REQUIRED)
  endif()
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

if(LIGO_TIDY)
  set(CMAKE_CXX_CLANG_TIDY
    clang-tidy;
    --config-file=${CMAKE_CURRENT_SOURCE_DIR}/.clang-tidy;
    --header-filter=${CMAKE_CURRENT_SOURCE_DIR}/include;
    --warnings-as-errors=*;)
endif(LIGO_TIDY)

add_library(${PROJECT_NAME} STATIC
  src/concrete_objects.cpp
  src/abstract_objects.cpp
  src/handle.cpp
  src/abstract_objects.cpp
  src/python_module.cpp
  src/python_types.cpp
  src/python_methods.cpp)
target_link_libraries(${PROJECT_NAME} PUBLIC fmt Metal Python::Module)
target_include_directories(${PROJECT_NAME} PUBLIC include/)
target_include_directories(${PROJECT_NAME} PUBLIC ${Python_INCLUDE_DIRS})

set_target_properties(${PROJECT_NAME} PROPERTIES
    POSITION_INDEPENDENT_CODE ON)

execute_process(
  COMMAND "${Python_EXECUTABLE}" "-c"
    "import sysconfig; print(sysconfig.get_config_var('EXT_SUFFIX'))"
  RESULT_VARIABLE LIGO_SUFFIX_RET
  OUTPUT_VARIABLE LIGO_SUFFIX
  OUTPUT_STRIP_TRAILING_WHITESPACE)

if (LIGO_SUFFIX_RET AND NOT LIGO_SUFFIX_RET EQUAL 0)
  message(FATAL_ERROR "Ligo failed to find correct value for 'EXT_SUFFIX'")
endif()
set(LIGO_SUFFIX ${LIGO_SUFFIX} CACHE INTERNAL "")

function(ligo_add_module name)
  add_library(${name} MODULE ${ARGN})
  if (MSVC)
    target_compile_options(${name} PRIVATE /bigobj /MP)
  endif()
  set_target_properties(${name} PROPERTIES PREFIX "" SUFFIX "${LIGO_SUFFIX}")
  set_target_properties(${name} PROPERTIES LINKER_LANGUAGE CXX)
  target_link_libraries(${name} PRIVATE ligo)
  set_target_properties(${name} PROPERTIES CXX_VISIBILITY_PRESET hidden)
endfunction()

add_subdirectory(tests)
