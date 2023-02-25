#ifndef INCLUDE_LIGO_IMPL_HANDLE_TPP_
#define INCLUDE_LIGO_IMPL_HANDLE_TPP_

#include "../handle.hpp"

#include "../python_types.hpp"
#include "../python_module.hpp"

namespace ligo {
  template <typename T>
  handle<T>::handle(PyObject* obj, python_module& mod) : _obj{obj}, _mod{mod} {}

  template <typename T>
  std::optional<handle<T>>
  handle<T>::from_cpp(const T& value, python_module& mod) {
    if (auto ft = mod.final_type(typeid(T))) {
      if (auto* obj = PyType_GenericAlloc(
            (PyTypeObject*)ft->get().type_object(), 0)) {
        std::bit_cast<pod<T>*>(obj)->value = value;
        return handle<T>(obj, mod);
      }
    }

    return {};
  }

  template <typename T>
  std::optional<handle<T>>
  handle<T>::from_python(PyObject* obj, python_module& mod) {
    if (auto ft = mod.final_type(typeid(T)))
      if (PyObject_TypeCheck(obj, (PyTypeObject*)ft->get().type_object()))
        return handle<T>(obj, mod);

    return {};
  }

  template <typename T>
  std::optional<handle<T>>
  handle<T>::from_python_with_casting(
      PyObject* obj, python_module& mod, temporary_list& temp_list) {
    if (auto ft = mod.final_type(typeid(T))) {
      PyTypeObject* type_object = (PyTypeObject*)ft->get().type_object();
      if (PyObject_TypeCheck(obj, type_object)) {
        return handle<T>(obj, mod);
      } else if (auto init = ft->get().initialiser()) {
        auto* cast_object = PyType_GenericAlloc(type_object, 0);
        if (cast_object) {
          PyObject* args[] = {cast_object, obj};
          if (init->get().internal_call(args, 2, mod, true)) {
            return handle<T>(cast_object, mod);
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
  handle<T>::operator T*() { return &std::bit_cast<pod<T>*>(_obj)->value; }
  template <typename T>
  handle<T>::operator T() const { return std::bit_cast<pod<T>*>(_obj)->value; }
  template <typename T>
  handle<T>::operator T&() { return std::bit_cast<pod<T>*>(_obj)->value; }

  template <typename T>
  PyObject* handle<T>::object() { return _obj; }
}

#endif  // INCLUDE_LIGO_IMPL_HANDLE_TPP_
