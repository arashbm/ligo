#include <ligo/ligo.hpp>

LIGO_MODULE(test_concrete_objects_ext, "module for testing concrete types", mod) {
  mod.overload_method("none_arg",
                      [](ligo::python_none&) { Py_RETURN_TRUE; }, {"a"});
  mod.overload_method("none_arg", [](PyObject*) { Py_RETURN_FALSE; }, {"a"});


  mod.overload_method("bool_arg",
                      [](ligo::python_bool&) { Py_RETURN_TRUE; }, {"a"});
  mod.overload_method("bool_arg",
                      [](PyObject*) { Py_RETURN_FALSE; }, {"a"});


  mod.overload_method("long_arg",
                      [](ligo::python_long&) { Py_RETURN_TRUE; }, {"a"});
  mod.overload_method("long_arg", [](PyObject*) { Py_RETURN_FALSE; }, {"a"});


  mod.overload_method("float_arg",
                      [](ligo::python_float&) { Py_RETURN_TRUE; }, {"a"});
  mod.overload_method("float_arg", [](PyObject*) { Py_RETURN_FALSE; }, {"a"});


  mod.overload_method("complex_arg",
                      [](ligo::python_complex&) { Py_RETURN_TRUE; }, {"a"});
  mod.overload_method("complex_arg", [](PyObject*) { Py_RETURN_FALSE; }, {"a"});


  mod.overload_method("unicode_arg",
                      [](ligo::python_unicode&) { Py_RETURN_TRUE; }, {"a"});
  mod.overload_method("unicode_arg", [](PyObject*) { Py_RETURN_FALSE; }, {"a"});


  mod.overload_method("tuple_arg",
                      [](ligo::python_tuple&) { Py_RETURN_TRUE; }, {"a"});
  mod.overload_method("tuple_arg",
                      [](PyObject*) { Py_RETURN_FALSE; }, {"a"});


  mod.overload_method("list_arg",
                      [](ligo::python_list&) { Py_RETURN_TRUE; }, {"a"});
  mod.overload_method("list_arg", [](PyObject*) { Py_RETURN_FALSE; }, {"a"});


  mod.overload_method("dictionary_arg",
                      [](ligo::python_dictionary&) { Py_RETURN_TRUE; }, {"a"});
  mod.overload_method("dictionary_arg",
                      [](PyObject*) { Py_RETURN_FALSE; }, {"a"});


  mod.overload_method("set_arg",
                      [](ligo::python_set&) { Py_RETURN_TRUE; }, {"a"});
  mod.overload_method("set_arg", [](PyObject*) { Py_RETURN_FALSE; }, {"a"});
}
