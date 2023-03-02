function(add_copy_bench_custom_command name)
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

ligo_add_module(bench_methods_ext MODULE EXCLUDE_FROM_ALL bench_methods.cpp)
add_copy_bench_custom_command(bench_methods.py)

add_custom_target(ligo_bench DEPENDS
  bench_methods.py bench_methods_ext)
