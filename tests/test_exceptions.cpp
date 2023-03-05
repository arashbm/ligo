#include <ligo/ligo.hpp>

PyObject* test_python_exception() {
  PyErr_SetString(PyExc_RuntimeError, "threw python_exception");
  throw ligo::python_exception();
  Py_RETURN_TRUE;
}

PyObject* test_throw_object() {
  throw 13;  // NOLINT
  Py_RETURN_TRUE;
}

PyObject* test_bad_alloc() {
  throw std::bad_alloc();
  Py_RETURN_TRUE;
}

PyObject* test_domain_error() {
  throw std::domain_error("threw domain_error");
  Py_RETURN_TRUE;
}

PyObject* test_invalid_argument() {
  throw std::invalid_argument("threw invalid_argument");
  Py_RETURN_TRUE;
}

PyObject* test_length_error() {
  throw std::length_error("threw length_error");
  Py_RETURN_TRUE;
}

PyObject* test_out_of_range() {
  throw std::out_of_range("threw out_of_range");
  Py_RETURN_TRUE;
}

PyObject* test_range_error() {
  throw std::range_error("threw range_error");
  Py_RETURN_TRUE;
}

PyObject* test_overflow_error() {
  throw std::overflow_error("threw overflow_error");
  Py_RETURN_TRUE;
}

PyObject* test_exception() {
  throw std::exception();
  Py_RETURN_TRUE;
}

class hello_exception : public std::exception {
public:
  [[nodiscard]] const char* what() const noexcept override {
    return "threw hello_exception";
  }
};


PyObject* test_exception_subclass() {
  throw hello_exception();
  Py_RETURN_TRUE;
}


LIGO_MODULE(test_exceptions_ext, "module for testing exception translation", mod) {
  mod.define_method("test_python_exception", &test_python_exception, {});
  mod.define_method("test_throw_object", &test_throw_object, {});
  mod.define_method("test_bad_alloc", &test_bad_alloc, {});
  mod.define_method("test_domain_error", &test_domain_error, {});
  mod.define_method("test_invalid_argument", &test_invalid_argument, {});
  mod.define_method("test_length_error", &test_length_error, {});
  mod.define_method("test_out_of_range", &test_out_of_range, {});
  mod.define_method("test_range_error", &test_range_error, {});
  mod.define_method("test_overflow_error", &test_overflow_error, {});
  mod.define_method("test_exception", &test_exception, {});
  mod.define_method("test_exception_subclass", &test_exception_subclass, {});
}
