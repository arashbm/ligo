#include "../include/ligo/abstract_objects.hpp"

namespace ligo {
  python_object::python_object(PyObject* obj) : _object{obj} {}
  PyObject* python_object::object() const { return _object; }

  handle<python_object>::handle(PyObject* obj, python_module& /*mod*/)
    : _obj{obj} {}

  std::optional<handle<python_object>>
  handle<python_object>::from_cpp(
      const python_object& cpp_obj, python_module& mod) {
    return handle<python_object>(cpp_obj.object(), mod);
  }

  std::optional<handle<python_object>>
  handle<python_object>::from_python(PyObject* obj, python_module& mod) {
    return handle<python_object>(obj, mod);
  }

  std::optional<handle<python_object>>
  handle<python_object>::from_python_with_casting(
      PyObject* obj, python_module& mod, temporary_list& /* tmp_list */) {
    return from_python(obj, mod);
  }

  handle<python_object>::operator python_object*() { return &_obj; }
  handle<python_object>::operator python_object() const { return _obj; }
  handle<python_object>::operator python_object&() { return _obj; }

  PyObject* handle<python_object>::object() { return _obj.object(); }



  python_callable::python_callable(PyObject* obj) : _object{obj} {}
  PyObject* python_callable::object() const { return _object; }

  handle<python_callable>::handle(PyObject* obj, python_module& /*mod*/)
    : _obj{obj} {}

  std::optional<handle<python_callable>>
  handle<python_callable>::from_cpp(
      const python_callable& cpp_obj, python_module& mod) {
    return handle<python_callable>(cpp_obj.object(), mod);
  }

  std::optional<handle<python_callable>>
  handle<python_callable>::from_python(PyObject* obj, python_module& mod) {
    if (PyCallable_Check(obj) != 0)
      return handle<python_callable>(obj, mod);
    return {};
  }

  std::optional<handle<python_callable>>
  handle<python_callable>::from_python_with_casting(
      PyObject* obj, python_module& mod, temporary_list& /* tmp_list */) {
    return from_python(obj, mod);
  }

  handle<python_callable>::operator python_callable*() { return &_obj; }
  handle<python_callable>::operator python_callable() const { return _obj; }
  handle<python_callable>::operator python_callable&() { return _obj; }

  PyObject* handle<python_callable>::object() { return _obj.object(); }




  python_number::python_number(PyObject* obj) : _object{obj} {}
  PyObject* python_number::object() const { return _object; }

  handle<python_number>::handle(PyObject* obj, python_module& /*mod*/)
    : _obj{obj} {}

  std::optional<handle<python_number>>
  handle<python_number>::from_cpp(
      const python_number& cpp_obj, python_module& mod) {
    return handle<python_number>(cpp_obj.object(), mod);
  }

  std::optional<handle<python_number>>
  handle<python_number>::from_python(PyObject* obj, python_module& mod) {
    if (PyNumber_Check(obj) != 0)
      return handle<python_number>(obj, mod);
    return {};
  }

  std::optional<handle<python_number>>
  handle<python_number>::from_python_with_casting(
      PyObject* obj, python_module& mod, temporary_list& /* tmp_list */) {
    return from_python(obj, mod);
  }

  handle<python_number>::operator python_number*() { return &_obj; }

  handle<python_number>::operator python_number() const { return _obj; }

  handle<python_number>::operator python_number&() { return _obj; }

  PyObject* handle<python_number>::object() { return _obj.object(); }



  python_index::python_index(PyObject* obj) : _object{obj} {}
  PyObject* python_index::object() const { return _object; }

  handle<python_index>::handle(PyObject* obj, python_module& /*mod*/)
    : _obj{obj} {}

  std::optional<handle<python_index>>
  handle<python_index>::from_cpp(
      const python_index& cpp_obj, python_module& mod) {
    return handle<python_index>(cpp_obj.object(), mod);
  }

  std::optional<handle<python_index>>
  handle<python_index>::from_python(PyObject* obj, python_module& mod) {
    if (PyIndex_Check(obj) != 0)
      return handle<python_index>(obj, mod);
    return {};
  }

  std::optional<handle<python_index>>
  handle<python_index>::from_python_with_casting(
      PyObject* obj, python_module& mod, temporary_list& /* tmp_list */) {
    return from_python(obj, mod);
  }

  handle<python_index>::operator python_index*() { return &_obj; }
  handle<python_index>::operator python_index() const { return _obj; }
  handle<python_index>::operator python_index&() { return _obj; }

  PyObject* handle<python_index>::object() { return _obj.object(); }



  python_sequence::python_sequence(PyObject* obj) : _object{obj} {}
  PyObject* python_sequence::object() const { return _object; }

  handle<python_sequence>::handle(PyObject* obj, python_module& /*mod*/)
    : _obj{obj} {}

  std::optional<handle<python_sequence>>
  handle<python_sequence>::from_cpp(
      const python_sequence& cpp_obj, python_module& mod) {
    return handle<python_sequence>(cpp_obj.object(), mod);
  }

  std::optional<handle<python_sequence>>
  handle<python_sequence>::from_python(PyObject* obj, python_module& mod) {
    if (PySequence_Check(obj) != 0)
      return handle<python_sequence>(obj, mod);
    return {};
  }

  std::optional<handle<python_sequence>>
  handle<python_sequence>::from_python_with_casting(
      PyObject* obj, python_module& mod, temporary_list& /* tmp_list */) {
    return from_python(obj, mod);
  }

  handle<python_sequence>::operator python_sequence*() { return &_obj; }

  handle<python_sequence>::operator python_sequence() const { return _obj; }

  handle<python_sequence>::operator python_sequence&() { return _obj; }

  PyObject* handle<python_sequence>::object() { return _obj.object(); }



  python_mapping::python_mapping(PyObject* obj) : _object{obj} {}
  PyObject* python_mapping::object() const { return _object; }

  handle<python_mapping>::handle(PyObject* obj, python_module& /*mod*/)
    : _obj{obj} {}

  std::optional<handle<python_mapping>>
  handle<python_mapping>::from_cpp(
      const python_mapping& cpp_obj, python_module& mod) {
    return handle<python_mapping>(cpp_obj.object(), mod);
  }

std::optional<handle<python_mapping>>
  handle<python_mapping>::from_python(PyObject* obj, python_module& mod) {
    if (PyMapping_Check(obj) != 0)
      return handle<python_mapping>(obj, mod);
    return {};
  }

  std::optional<handle<python_mapping>>
  handle<python_mapping>::from_python_with_casting(
      PyObject* obj, python_module& mod, temporary_list& /* tmp_list */) {
    return from_python(obj, mod);
  }

  handle<python_mapping>::operator python_mapping*() { return &_obj; }

  handle<python_mapping>::operator python_mapping() const { return _obj; }

  handle<python_mapping>::operator python_mapping&() { return _obj; }

  PyObject* handle<python_mapping>::object() { return _obj.object(); }



  python_iterator::python_iterator(PyObject* obj) : _object{obj} {}
  PyObject* python_iterator::object() const { return _object; }

  handle<python_iterator>::handle(PyObject* obj, python_module& /*mod*/)
    : _obj{obj} {}

  std::optional<handle<python_iterator>>
  handle<python_iterator>::from_cpp(
      const python_iterator& cpp_obj, python_module& mod) {
    return handle<python_iterator>(cpp_obj.object(), mod);
  }

  std::optional<handle<python_iterator>>
  handle<python_iterator>::from_python(PyObject* obj, python_module& mod) {
    if (PyIter_Check(obj) != 0)
      return handle<python_iterator>(obj, mod);
    return {};
  }

  std::optional<handle<python_iterator>>
  handle<python_iterator>::from_python_with_casting(
      PyObject* obj, python_module& mod, temporary_list& /* tmp_list */) {
    return from_python(obj, mod);
  }

  handle<python_iterator>::operator python_iterator*() { return &_obj; }

  handle<python_iterator>::operator python_iterator() const { return _obj; }

  handle<python_iterator>::operator python_iterator&() { return _obj; }

  PyObject* handle<python_iterator>::object() { return _obj.object(); }



  python_buffer::python_buffer(PyObject* obj) : _object{obj} {}
  PyObject* python_buffer::object() const { return _object; }

  handle<python_buffer>::handle(PyObject* obj, python_module& /*mod*/)
    : _obj{obj} {}

  std::optional<handle<python_buffer>>
  handle<python_buffer>::from_cpp(
      const python_buffer& cpp_obj, python_module& mod) {
    return handle<python_buffer>(cpp_obj.object(), mod);
  }

  std::optional<handle<python_buffer>>
  handle<python_buffer>::from_python(PyObject* obj, python_module& mod) {
    if (PyObject_CheckBuffer(obj) != 0)
      return handle<python_buffer>(obj, mod);
    return {};
  }

  std::optional<handle<python_buffer>>
  handle<python_buffer>::from_python_with_casting(
      PyObject* obj, python_module& mod, temporary_list& /* tmp_list */) {
    return from_python(obj, mod);
  }

  handle<python_buffer>::operator python_buffer*() { return &_obj; }

  handle<python_buffer>::operator python_buffer() const { return _obj; }

  handle<python_buffer>::operator python_buffer&() { return _obj; }

  PyObject* handle<python_buffer>::object() { return _obj.object(); }
}
