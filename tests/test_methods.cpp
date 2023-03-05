#include <ligo/ligo.hpp>

PyObject* test_function(PyObject* /* a */, PyObject* /* b */) noexcept {
  Py_RETURN_TRUE;
}

PyObject* test_function_noexcept(PyObject* /* a */, PyObject* /* b */) noexcept {
  Py_RETURN_TRUE;
}

LIGO_MODULE(test_methods_ext, "module for testing methods", mod) {
  mod.overload_method("simple_overloading", []() -> PyObject* {
                        Py_RETURN_TRUE;
                      }, {});
  mod.overload_method("simple_overloading", [](PyObject* obj) -> PyObject* {
                        Py_INCREF(obj);
                        return obj;
                      }, {"a"});

  mod.define_method("noexcept_lambda",
                    []() noexcept -> PyObject* { Py_RETURN_TRUE; }, {});
  mod.define_method("no_capture_lambda", []() -> PyObject* {
                      Py_RETURN_TRUE;
                    }, {});
  int a = 12, b = 43, c = 22, d = -1;  // NOLINT
  mod.define_method("capturing_lambda", [a, b, c, d]() -> PyObject* {
                      return PyLong_FromSize_t(a + b + c + d);
                    }, {});
  mod.define_method("fpointer", &test_function, {"a", "b"});
  mod.define_method("fpointer_noexcept", &test_function_noexcept, {"a", "b"});
}
