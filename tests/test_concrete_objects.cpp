#include <ligo/ligo.hpp>

static ligo::python_module mod("libtest_concrete_objects",
    "module for testing concrete types");

PyMODINIT_FUNC PyInit_libtest_concrete_objects() {
  ligo::overload_set none_arg("none_arg");
  none_arg.add_overload([](ligo::python_none& a) { Py_RETURN_TRUE; }, {"a"});
  none_arg.add_overload([](PyObject*) { Py_RETURN_FALSE; }, {"a"});
  mod.add_overload_set(none_arg);


  ligo::overload_set bool_arg("bool_arg");
  bool_arg.add_overload(
      [](ligo::python_bool& a) { Py_RETURN_TRUE; }, {"a"});
  bool_arg.add_overload([](PyObject*) { Py_RETURN_FALSE; }, {"a"});
  mod.add_overload_set(bool_arg);


  ligo::overload_set long_arg("long_arg");
  long_arg.add_overload(
      [](ligo::python_long& a) { Py_RETURN_TRUE; }, {"a"});
  long_arg.add_overload([](PyObject*) { Py_RETURN_FALSE; }, {"a"});
  mod.add_overload_set(long_arg);


  ligo::overload_set float_arg("float_arg");
  float_arg.add_overload(
      [](ligo::python_float& a) { Py_RETURN_TRUE; }, {"a"});
  float_arg.add_overload([](PyObject*) { Py_RETURN_FALSE; }, {"a"});
  mod.add_overload_set(float_arg);


  ligo::overload_set complex_arg("complex_arg");
  complex_arg.add_overload(
      [](ligo::python_complex& a) { Py_RETURN_TRUE; }, {"a"});
  complex_arg.add_overload([](PyObject*) { Py_RETURN_FALSE; }, {"a"});
  mod.add_overload_set(complex_arg);


  ligo::overload_set unicode_arg("unicode_arg");
  unicode_arg.add_overload([](ligo::python_unicode& a) {
      Py_RETURN_TRUE;
    }, {"a"});
  unicode_arg.add_overload([](PyObject*) { Py_RETURN_FALSE; }, {"a"});
  mod.add_overload_set(unicode_arg);


  ligo::overload_set tuple_arg("tuple_arg");
  tuple_arg.add_overload([](ligo::python_tuple& a) {
      Py_RETURN_TRUE;
    }, {"a"});
  tuple_arg.add_overload([](PyObject*) { Py_RETURN_FALSE; }, {"a"});
  mod.add_overload_set(tuple_arg);


  ligo::overload_set list_arg("list_arg");
  list_arg.add_overload([](ligo::python_list& a) {
      Py_RETURN_TRUE;
    }, {"a"});
  list_arg.add_overload([](PyObject*) { Py_RETURN_FALSE; }, {"a"});
  mod.add_overload_set(list_arg);


  ligo::overload_set dictionary_arg("dictionary_arg");
  dictionary_arg.add_overload([](ligo::python_dictionary& a) {
      Py_RETURN_TRUE;
    }, {"a"});
  dictionary_arg.add_overload([](PyObject*) { Py_RETURN_FALSE; }, {"a"});
  mod.add_overload_set(dictionary_arg);


  ligo::overload_set set_arg("set_arg");
  set_arg.add_overload([](ligo::python_set& a) {
      Py_RETURN_TRUE;
    }, {"a"});
  set_arg.add_overload([](PyObject*) { Py_RETURN_FALSE; }, {"a"});
  mod.add_overload_set(set_arg);

  return mod.init();
}
