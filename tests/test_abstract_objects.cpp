#include <ligo/ligo.hpp>

LIGO_MODULE(test_abstract_objects_ext, "module for testing abstract types", mod) {
  mod.overload_method("object_arg",
                      [](ligo::python_object& /* param */) {
                          Py_RETURN_TRUE;
                      }, {{"a"}});
  mod.overload_method("object_arg",
                      [](PyObject*) {
                          Py_RETURN_FALSE;
                      }, {{"a"}});


  mod.overload_method("callable_arg",
                      [](ligo::python_callable& /* param */) {
                          Py_RETURN_TRUE;
                      }, {{"a"}});
  mod.overload_method("callable_arg",
                      [](PyObject*) { Py_RETURN_FALSE; }, {{"a"}});


  mod.overload_method("number_arg",
                      [](ligo::python_number& /* param */) {
                          Py_RETURN_TRUE;
                      }, {{"a"}});
  mod.overload_method("number_arg",
                      [](PyObject*) {
                          Py_RETURN_FALSE;
                      }, {{"a"}});


  mod.overload_method("index_arg",
                      [](ligo::python_index& /* param */) {
                          Py_RETURN_TRUE;
                      }, {{"a"}});
  mod.overload_method("index_arg",
                      [](PyObject*) {
                          Py_RETURN_FALSE;
                      }, {{"a"}});


  mod.overload_method("sequence_arg",
                      [](ligo::python_sequence& /* param */) {
                          Py_RETURN_TRUE;
                      }, {{"a"}});
  mod.overload_method("sequence_arg",
                      [](PyObject*) {
                          Py_RETURN_FALSE;
                      }, {{"a"}});

  mod.overload_method("mapping_arg",
                      [](ligo::python_mapping& /* param */) {
                          Py_RETURN_TRUE;
                      }, {{"a"}});
  mod.overload_method("mapping_arg",
                      [](PyObject*) {
                          Py_RETURN_FALSE;
                      }, {{"a"}});
}
