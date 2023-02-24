#include "../include/ligo/concrete_objects.hpp"

namespace ligo {
  python_none::python_none(PyObject* /* obj */) {}
  PyObject* python_none::object() const { return Py_None; }

  handle<python_none>::handle(PyObject* obj, python_module& /* mod */)
    : _obj{obj} {}

  std::optional<handle<python_none>>
  handle<python_none>::from_cpp(
      const python_none& cpp_obj, python_module& mod) {
    return handle<python_none>(cpp_obj.object(), mod);
  }

  std::optional<handle<python_none>>
  handle<python_none>::from_python(PyObject* obj, python_module& mod) {
    if (obj == Py_None)
      return handle<python_none>(obj, mod);
    return {};
  }

  std::optional<handle<python_none>>
  handle<python_none>::from_python_with_casting(
      PyObject* obj, python_module& mod, temporary_list& /* tmp_list */) {
    return from_python(obj, mod);
  }

  handle<python_none>::operator python_none*() { return &_obj; }
  handle<python_none>::operator python_none() const { return _obj; }
  handle<python_none>::operator python_none&() { return _obj; }

  PyObject* handle<python_none>::object() { return Py_None; }



  python_bool::python_bool(PyObject* obj) : _object{obj} {}
  PyObject* python_bool::object() const { return _object; }

  handle<python_bool>::handle(PyObject* obj, python_module& /* mod */)
    : _obj{obj} {}

  std::optional<handle<python_bool>>
  handle<python_bool>::from_cpp(
      const python_bool& cpp_obj, python_module& mod) {
    return handle<python_bool>(cpp_obj.object(), mod);
  }

  std::optional<handle<python_bool>>
  handle<python_bool>::from_python(PyObject* obj, python_module& mod) {
    if (PyBool_Check(obj))
      return handle<python_bool>(obj, mod);
    return {};
  }

  std::optional<handle<python_bool>>
  handle<python_bool>::from_python_with_casting(
      PyObject* obj, python_module& mod, temporary_list& /* tmp_list */) {
    return from_python(obj, mod);
  }

  handle<python_bool>::operator python_bool*() { return &_obj; }
  handle<python_bool>::operator python_bool() const { return _obj; }
  handle<python_bool>::operator python_bool&() { return _obj; }

  PyObject* handle<python_bool>::object() { return _obj.object(); }



  python_long::python_long(PyObject* obj) : _object{obj} {}
  PyObject* python_long::object() const { return _object; }

  handle<python_long>::handle(PyObject* obj, python_module& /* mod */)
    : _obj{obj} {}

  std::optional<handle<python_long>>
  handle<python_long>::from_cpp(
      const python_long& cpp_obj, python_module& mod) {
    return handle<python_long>(cpp_obj.object(), mod);
  }

  std::optional<handle<python_long>>
  handle<python_long>::from_python(PyObject* obj, python_module& mod) {
    if (PyLong_Check(obj))
      return handle<python_long>(obj, mod);

    return {};
  }

  std::optional<handle<python_long>>
  handle<python_long>::from_python_with_casting(
      PyObject* obj, python_module& mod, temporary_list& temp_list) {
    if (PyLong_Check(obj))
      return handle<python_long>(obj, mod);

    if (auto* idx = PyNumber_Index(obj)) {
      temp_list.add(idx);
      return handle<python_long>(idx, mod);
    }

    return {};
  }

  handle<python_long>::operator python_long*() { return &_obj; }
  handle<python_long>::operator python_long() const { return _obj; }
  handle<python_long>::operator python_long&() { return _obj; }

  PyObject* handle<python_long>::object() { return _obj.object(); }



  python_float::python_float(PyObject* obj) : _object{obj} {}
  PyObject* python_float::object() const { return _object; }

  handle<python_float>::handle(PyObject* obj, python_module& /* mod */)
    : _obj{obj} {}

  std::optional<handle<python_float>>
  handle<python_float>::from_cpp(
      const python_float& cpp_obj, python_module& mod) {
    return handle<python_float>(cpp_obj.object(), mod);
  }

  std::optional<handle<python_float>>
  handle<python_float>::from_python(PyObject* obj, python_module& mod) {
    if (PyFloat_Check(obj))
      return handle<python_float>(obj, mod);

    return {};
  }

  std::optional<handle<python_float>>
  handle<python_float>::from_python_with_casting(
      PyObject* obj, python_module& mod, temporary_list& temp_list) {
    if (PyFloat_Check(obj))
      return handle<python_float>(obj, mod);

    if (auto* flt = PyNumber_Float(obj)) {
      temp_list.add(flt);
      return handle<python_float>(flt, mod);
    }

    return {};
  }

  handle<python_float>::operator python_float*() { return &_obj; }
  handle<python_float>::operator python_float() const { return _obj; }
  handle<python_float>::operator python_float&() { return _obj; }

  PyObject* handle<python_float>::object() { return _obj.object(); }




  python_complex::python_complex(PyObject* obj) : _object{obj} {}
  PyObject* python_complex::object() const { return _object; }

  handle<python_complex>::handle(PyObject* obj, python_module& /* mod */)
    : _obj{obj} {}

  std::optional<handle<python_complex>>
  handle<python_complex>::from_cpp(
      const python_complex& cpp_obj, python_module& mod) {
    return handle<python_complex>(cpp_obj.object(), mod);
  }

  std::optional<handle<python_complex>>
  handle<python_complex>::from_python(PyObject* obj, python_module& mod) {
    if (PyComplex_Check(obj))
      return handle<python_complex>(obj, mod);

    return {};
  }

  std::optional<handle<python_complex>>
  handle<python_complex>::from_python_with_casting(
      PyObject* obj, python_module& mod, temporary_list& /* tmp_list */) {
    return from_python(obj, mod);
  }

  handle<python_complex>::operator python_complex*() { return &_obj; }
  handle<python_complex>::operator python_complex() const { return _obj; }
  handle<python_complex>::operator python_complex&() { return _obj; }

  PyObject* handle<python_complex>::object() { return _obj.object(); }




  python_unicode::python_unicode(PyObject* obj) : _object{obj} {}
  PyObject* python_unicode::object() const { return _object; }

  handle<python_unicode>::handle(PyObject* obj, python_module& /* mod */)
    : _obj{obj} {}

  std::optional<handle<python_unicode>>
  handle<python_unicode>::from_cpp(
      const python_unicode& cpp_obj, python_module& mod) {
    return handle<python_unicode>(cpp_obj.object(), mod);
  }

  std::optional<handle<python_unicode>>
  handle<python_unicode>::from_python(PyObject* obj, python_module& mod) {
    if (PyUnicode_Check(obj))
      return handle<python_unicode>(obj, mod);

    return {};
  }

  std::optional<handle<python_unicode>>
  handle<python_unicode>::from_python_with_casting(
      PyObject* obj, python_module& mod, temporary_list& /* tmp_list */) {
    return from_python(obj, mod);
  }

  handle<python_unicode>::operator python_unicode*() { return &_obj; }
  handle<python_unicode>::operator python_unicode() const { return _obj; }
  handle<python_unicode>::operator python_unicode&() { return _obj; }

  PyObject* handle<python_unicode>::object() { return _obj.object(); }



  python_tuple::python_tuple(PyObject* obj) : _object{obj} {}
  PyObject* python_tuple::object() const { return _object; }

  handle<python_tuple>::handle(PyObject* obj, python_module& /* mod */)
    : _obj{obj} {}

  std::optional<handle<python_tuple>>
  handle<python_tuple>::from_cpp(
      const python_tuple& cpp_obj, python_module& mod) {
    return handle<python_tuple>(cpp_obj.object(), mod);
  }

  std::optional<handle<python_tuple>>
  handle<python_tuple>::from_python(PyObject* obj, python_module& mod) {
    if (PyTuple_Check(obj))
      return handle<python_tuple>(obj, mod);

    return {};
  }

  std::optional<handle<python_tuple>>
  handle<python_tuple>::from_python_with_casting(
      PyObject* obj, python_module& mod, temporary_list& /* tmp_list */) {
    return from_python(obj, mod);
  }

  handle<python_tuple>::operator python_tuple*() { return &_obj; }
  handle<python_tuple>::operator python_tuple() const { return _obj; }
  handle<python_tuple>::operator python_tuple&() { return _obj; }

  PyObject* handle<python_tuple>::object() { return _obj.object(); }




  python_list::python_list(PyObject* obj) : _object{obj} {}
  PyObject* python_list::object() const { return _object; }

  handle<python_list>::handle(PyObject* obj, python_module& /* mod */)
    : _obj{obj} {}

  std::optional<handle<python_list>>
  handle<python_list>::from_cpp(
      const python_list& cpp_obj, python_module& mod) {
    return handle<python_list>(cpp_obj.object(), mod);
  }

  std::optional<handle<python_list>>
  handle<python_list>::from_python(PyObject* obj, python_module& mod) {
    if (PyList_Check(obj))
      return handle<python_list>(obj, mod);

    return {};
  }

  std::optional<handle<python_list>>
  handle<python_list>::from_python_with_casting(
      PyObject* obj, python_module& mod, temporary_list& /* tmp_list */) {
    return from_python(obj, mod);
  }

  handle<python_list>::operator python_list*() { return &_obj; }
  handle<python_list>::operator python_list() const { return _obj; }
  handle<python_list>::operator python_list&() { return _obj; }

  PyObject* handle<python_list>::object() { return _obj.object(); }





  python_dictionary::python_dictionary(PyObject* obj) : _object{obj} {}
  PyObject* python_dictionary::object() const { return _object; }

  handle<python_dictionary>::handle(PyObject* obj, python_module& /* mod */)
    : _obj{obj} {}

  std::optional<handle<python_dictionary>>
  handle<python_dictionary>::from_cpp(
      const python_dictionary& cpp_obj, python_module& mod) {
    return handle<python_dictionary>(cpp_obj.object(), mod);
  }

  std::optional<handle<python_dictionary>>
  handle<python_dictionary>::from_python(PyObject* obj, python_module& mod) {
    if (PyDict_Check(obj))
      return handle<python_dictionary>(obj, mod);

    return {};
  }

  std::optional<handle<python_dictionary>>
  handle<python_dictionary>::from_python_with_casting(
      PyObject* obj, python_module& mod, temporary_list& /* tmp_list */) {
    return from_python(obj, mod);
  }

  handle<python_dictionary>::operator python_dictionary*() { return &_obj; }
  handle<python_dictionary>::operator python_dictionary() const { return _obj; }
  handle<python_dictionary>::operator python_dictionary&() { return _obj; }

  PyObject* handle<python_dictionary>::object() { return _obj.object(); }



  python_set::python_set(PyObject* obj) : _object{obj} {}
  PyObject* python_set::object() const { return _object; }

  handle<python_set>::handle(PyObject* obj, python_module& /* mod */)
    : _obj{obj} {}

  std::optional<handle<python_set>>
  handle<python_set>::from_cpp(const python_set& cpp_obj, python_module& mod) {
    return handle<python_set>(cpp_obj.object(), mod);
  }

  std::optional<handle<python_set>>
  handle<python_set>::from_python(PyObject* obj, python_module& mod) {
    if (PySet_Check(obj))
      return handle<python_set>(obj, mod);

    return {};
  }

  std::optional<handle<python_set>>
  handle<python_set>::from_python_with_casting(
      PyObject* obj, python_module& mod, temporary_list& /* tmp_list */) {
    return from_python(obj, mod);
  }

  handle<python_set>::operator python_set*() { return &_obj; }
  handle<python_set>::operator python_set() const { return _obj; }
  handle<python_set>::operator python_set&() { return _obj; }

  PyObject* handle<python_set>::object() { return _obj.object(); }
}  // namespace ligo
