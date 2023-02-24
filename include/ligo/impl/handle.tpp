#ifndef INCLUDE_LIGO_IMPL_HANDLE_TPP_
#define INCLUDE_LIGO_IMPL_HANDLE_TPP_

#include "../handle.hpp"

#include "../python_types.hpp"
#include "../python_module.hpp"

namespace ligo {
  template <typename T>
  handle<T>::handle(PyObject* o, python_module& m) : _o{o}, _m{m} {}

  template <typename T>
  std::optional<handle<T>>
  handle<T>::from_cpp(const T& value, python_module& m) {
    if (auto ft = m.final_type(typeid(T))) {
      if (auto o = PyType_GenericAlloc(
            (PyTypeObject*)ft->get().type_object(), 0)) {
        std::bit_cast<pod<T>*>(o)->value = value;
        return handle<T>(o, m);
      }
    }

    return {};
  }

  template <typename T>
  std::optional<handle<T>>
  handle<T>::from_python(PyObject* o, python_module& m) {
    if (auto ft = m.final_type(typeid(T)))
      if (PyObject_TypeCheck(o, (PyTypeObject*)ft->get().type_object()))
        return handle<T>(o, m);

    return {};
  }

  template <typename T>
  std::optional<handle<T>>
  handle<T>::from_python_with_casting(
      PyObject* o, python_module& m, temporary_list& temp_list) {
    if (auto ft = m.final_type(typeid(T))) {
      PyTypeObject* type_object = (PyTypeObject*)ft->get().type_object();
      if (PyObject_TypeCheck(o, type_object)) {
        return handle<T>(o, m);
      } else if (auto init = ft->get().initialiser()) {
        auto cast_object = PyType_GenericAlloc(type_object, 0);
        if (cast_object) {
          PyObject* args[] = {cast_object, o};
          if (init->get().internal_call(args, 2, m, true)) {
            return handle<T>(cast_object, m);
          } else {
            Py_DECREF(cast_object);
            PyErr_Clear();
          }
        }
      }
    }

    return {};
  }

  template <typename T>
  handle<T>::operator T*() { return &std::bit_cast<pod<T>*>(_o)->value; }
  template <typename T>
  handle<T>::operator T() const { return std::bit_cast<pod<T>*>(_o)->value; }
  template <typename T>
  handle<T>::operator T&() { return std::bit_cast<pod<T>*>(_o)->value; }

  template <typename T>
  PyObject* handle<T>::object() { return _o; }
}

#endif  // INCLUDE_LIGO_IMPL_HANDLE_TPP_
