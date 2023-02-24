add_library(test_methods MODULE test_methods.cpp)
target_link_libraries(test_methods PUBLIC ligo Python::Module)
add_custom_command(
  DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/test_methods.py
  TARGET OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/test_methods.py
  COMMAND ${CMAKE_COMMAND} -E copy_if_different
  ${CMAKE_CURRENT_SOURCE_DIR}/test_methods.py ${CMAKE_CURRENT_BINARY_DIR})

add_library(test_exceptions MODULE test_exceptions.cpp)
target_link_libraries(test_exceptions PUBLIC ligo Python::Module)
add_custom_command(
  DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/test_exceptions.py
  TARGET OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/test_exceptions.py
  COMMAND ${CMAKE_COMMAND} -E copy_if_different
  ${CMAKE_CURRENT_SOURCE_DIR}/test_exceptions.py ${CMAKE_CURRENT_BINARY_DIR})


add_library(test_types MODULE test_types.cpp)
target_link_libraries(test_types PUBLIC ligo Python::Module)
add_custom_command(
  DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/test_types.py
  TARGET OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/test_types.py
  COMMAND ${CMAKE_COMMAND} -E copy_if_different
  ${CMAKE_CURRENT_SOURCE_DIR}/test_types.py ${CMAKE_CURRENT_BINARY_DIR})


add_library(test_abstract_objects MODULE test_abstract_objects.cpp)
target_link_libraries(test_abstract_objects PUBLIC ligo Python::Module)
add_custom_command(
  DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/test_abstract_objects.py
  TARGET OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/test_abstract_objects.py
  COMMAND ${CMAKE_COMMAND} -E copy_if_different
  ${CMAKE_CURRENT_SOURCE_DIR}/test_abstract_objects.py
  ${CMAKE_CURRENT_BINARY_DIR})

add_library(test_concrete_objects MODULE test_concrete_objects.cpp)
target_link_libraries(test_concrete_objects PUBLIC ligo Python::Module)
add_custom_command(
  DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/test_concrete_objects.py
  TARGET OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/test_concrete_objects.py
  COMMAND ${CMAKE_COMMAND} -E copy_if_different
  ${CMAKE_CURRENT_SOURCE_DIR}/test_concrete_objects.py
  ${CMAKE_CURRENT_BINARY_DIR})

add_custom_target(copy-tests ALL DEPENDS test_methods.py test_types.py
  test_exceptions.py test_abstract_objects.py test_concrete_objects.py)
