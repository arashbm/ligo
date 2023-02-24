#include <ligo/ligo.hpp>

static ligo::python_module mod("libtest_methods", "module for testing methods");

PyObject* test_function(PyObject*, PyObject*) {
  Py_RETURN_TRUE;
}

PyObject* test_function_noexcept(PyObject*, PyObject*) noexcept {
  Py_RETURN_TRUE;
}

PyMODINIT_FUNC PyInit_libtest_methods() {
  ligo::overload_set so("simple_overloading");
  so.add_overload([]() -> PyObject* { Py_RETURN_TRUE; }, {});
  so.add_overload([](PyObject* a) -> PyObject* {
      Py_INCREF(a);
      return a;
  }, {"a"});
  mod.add_overload_set(so);

  ligo::overload_set noexcept_lambda("noexcept_lambda");
  noexcept_lambda.add_overload(
      []() noexcept -> PyObject* { Py_RETURN_TRUE; }, {});
  mod.add_overload_set(noexcept_lambda);

  ligo::overload_set no_capture("no_capture_lambda");
  no_capture.add_overload([]() -> PyObject* { Py_RETURN_TRUE; }, {});
  mod.add_overload_set(no_capture);

  int a = 12, b = 43, c = 22, d = -1;
  ligo::overload_set capturing_lambda("capturing_lambda");
  capturing_lambda.add_overload([a, b, c, d]() -> PyObject* {
      return PyLong_FromSize_t(a + b + c + d);
    }, {});
  mod.add_overload_set(capturing_lambda);

  ligo::overload_set fpointer("fpointer");
  fpointer.add_overload(&test_function, {"a", "b"});
  mod.add_overload_set(fpointer);

  ligo::overload_set fpointer_noexcept("fpointer_noexcept");
  fpointer_noexcept.add_overload(&test_function_noexcept, {"a", "b"});
  mod.add_overload_set(fpointer_noexcept);

  return mod.init();
}
