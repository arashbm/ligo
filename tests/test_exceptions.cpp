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
  ligo::overload_set tpe("test_python_exception");
  tpe.add_overload(&test_python_exception, {});
  mod.add_overload_set(tpe);

  ligo::overload_set tto("test_throw_object");
  tto.add_overload(&test_throw_object, {});
  mod.add_overload_set(tto);

  ligo::overload_set tba("test_bad_alloc");
  tba.add_overload(&test_bad_alloc, {});
  mod.add_overload_set(tba);

  ligo::overload_set tde("test_domain_error");
  tde.add_overload(&test_domain_error, {});
  mod.add_overload_set(tde);

  ligo::overload_set tia("test_invalid_argument");
  tia.add_overload(&test_invalid_argument, {});
  mod.add_overload_set(tia);

  ligo::overload_set tle("test_length_error");
  tle.add_overload(&test_length_error, {});
  mod.add_overload_set(tle);

  ligo::overload_set toor("test_out_of_range");
  toor.add_overload(&test_out_of_range, {});
  mod.add_overload_set(toor);

  ligo::overload_set tre("test_range_error");
  tre.add_overload(&test_range_error, {});
  mod.add_overload_set(tre);

  ligo::overload_set toe("test_overflow_error");
  toe.add_overload(&test_overflow_error, {});
  mod.add_overload_set(toe);

  ligo::overload_set tef("test_exception");
  tef.add_overload(&test_exception, {});
  mod.add_overload_set(tef);

  ligo::overload_set tes("test_exception_subclass");
  tes.add_overload(&test_exception_subclass, {});
  mod.add_overload_set(tes);
}
