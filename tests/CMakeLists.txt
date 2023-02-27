function(add_copy_test_custom_command name)
  if (MSVC)
    set(OUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>)
  else()
    set(OUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
  endif()
  
  add_custom_command(
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/${name}
    TARGET OUTPUT ${OUT_DIRECTORY}/${name}
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${CMAKE_CURRENT_SOURCE_DIR}/${name} ${OUT_DIRECTORY})
endfunction()

ligo_add_module(test_methods_ext MODULE EXCLUDE_FROM_ALL test_methods.cpp)
add_copy_test_custom_command(test_methods.py)

ligo_add_module(test_exceptions_ext MODULE EXCLUDE_FROM_ALL test_exceptions.cpp)
add_copy_test_custom_command(test_exceptions.py)


ligo_add_module(test_types_ext MODULE EXCLUDE_FROM_ALL test_types.cpp)
add_copy_test_custom_command(test_types.py)


ligo_add_module(test_abstract_objects_ext MODULE EXCLUDE_FROM_ALL test_abstract_objects.cpp)
add_copy_test_custom_command(test_abstract_objects.py)

ligo_add_module(test_concrete_objects_ext MODULE EXCLUDE_FROM_ALL test_concrete_objects.cpp)
add_copy_test_custom_command(test_concrete_objects.py)

add_custom_target(ligo_tests DEPENDS
  test_methods.py test_methods_ext
  test_types.py test_types_ext
  test_exceptions.py test_exceptions_ext
  test_abstract_objects.py test_abstract_objects_ext
  test_concrete_objects.py test_concrete_objects_ext)
