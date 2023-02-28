#include <ligo/ligo.hpp>

LIGO_MODULE(test_abstract_objects_ext, "module for testing abstract types", mod) {
  ligo::overload_set object_arg("object_arg");
  object_arg.add_overload(
      [](ligo::python_object& /* param */) { Py_RETURN_TRUE; }, {"a"});
  object_arg.add_overload([](PyObject*) { Py_RETURN_FALSE; }, {"a"});
  mod.add_overload_set(object_arg);


  ligo::overload_set callable_arg("callable_arg");
  callable_arg.add_overload(
      [](ligo::python_callable& /* param */) { Py_RETURN_TRUE; }, {"a"});
  callable_arg.add_overload([](PyObject*) { Py_RETURN_FALSE; }, {"a"});
  mod.add_overload_set(callable_arg);


  ligo::overload_set number_arg("number_arg");
  number_arg.add_overload(
      [](ligo::python_number& /* param */) { Py_RETURN_TRUE; }, {"a"});
  number_arg.add_overload([](PyObject*) { Py_RETURN_FALSE; }, {"a"});
  mod.add_overload_set(number_arg);


  ligo::overload_set index_arg("index_arg");
  index_arg.add_overload(
      [](ligo::python_index& /* param */) { Py_RETURN_TRUE; }, {"a"});
  index_arg.add_overload([](PyObject*) { Py_RETURN_FALSE; }, {"a"});
  mod.add_overload_set(index_arg);


  ligo::overload_set sequence_arg("sequence_arg");
  sequence_arg.add_overload(
      [](ligo::python_sequence& /* param */) { Py_RETURN_TRUE; }, {"a"});
  sequence_arg.add_overload([](PyObject*) { Py_RETURN_FALSE; }, {"a"});
  mod.add_overload_set(sequence_arg);


  ligo::overload_set mapping_arg("mapping_arg");
  mapping_arg.add_overload([](ligo::python_mapping& /* param */) {
      Py_RETURN_TRUE;
    }, {"a"});
  mapping_arg.add_overload([](PyObject*) { Py_RETURN_FALSE; }, {"a"});
  mod.add_overload_set(mapping_arg);
}
