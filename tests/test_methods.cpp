#include <ligo/ligo.hpp>

static ligo::python_module mod("libtest_methods", "module for testing methods");

PyObject* test_function(PyObject* /* a */, PyObject* /* b */) noexcept {
  Py_RETURN_TRUE;
}

PyObject* test_function_noexcept(PyObject* /* a */, PyObject* /* b */) noexcept {
  Py_RETURN_TRUE;
}

PyMODINIT_FUNC PyInit_libtest_methods() {
  ligo::overload_set simple_set("simple_overloading");
  simple_set.add_overload([]() -> PyObject* { Py_RETURN_TRUE; }, {});
  simple_set.add_overload([](PyObject* obj) -> PyObject* {
      Py_INCREF(obj);
      return obj;
  }, {"a"});
  mod.add_overload_set(simple_set);

  ligo::overload_set noexcept_lambda("noexcept_lambda");
  noexcept_lambda.add_overload(
      []() noexcept -> PyObject* { Py_RETURN_TRUE; }, {});
  mod.add_overload_set(noexcept_lambda);

  ligo::overload_set no_capture("no_capture_lambda");
  no_capture.add_overload([]() -> PyObject* { Py_RETURN_TRUE; }, {});
  mod.add_overload_set(no_capture);

  int a = 12, b = 43, c = 22, d = -1;  // NOLINT
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
