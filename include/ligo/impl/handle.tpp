#ifndef INCLUDE_LIGO_IMPL_HANDLE_TPP_
#define INCLUDE_LIGO_IMPL_HANDLE_TPP_

#include <array>

#include "../handle.hpp"

#include "../bit_cast.hpp"
#include "../python_types.hpp"
#include "../python_module.hpp"

namespace ligo {
  template <typename T>
  handle<T>::handle(PyObject* obj, python_module& mod) : _obj{obj}, _mod{mod} {}

  template <typename T>
  std::optional<handle<T>>
  handle<T>::from_cpp(const T& value, python_module& mod) {
    if (auto ftype = mod.final_type(typeid(T))) {
      if (auto* obj = PyType_GenericAlloc(
            (PyTypeObject*)ftype->get().type_object(), 0)) {
        bit_cast<pod<T>*>(obj)->value = value;
        return handle<T>(obj, mod);
      }
    }

    return {};
  }

  template <typename T>
  std::optional<handle<T>>
  handle<T>::from_python(PyObject* obj, python_module& mod) {
    if (auto ftype = mod.final_type(typeid(T)))
      if (PyObject_TypeCheck(obj, (PyTypeObject*)ftype->get().type_object()))
        return handle<T>(obj, mod);

    return {};
  }

  template <typename T>
  std::optional<handle<T>>
  handle<T>::from_python_with_casting(
      PyObject* obj, python_module& mod, temporary_list& /* tmp_list */) {
    if (auto ftype = mod.final_type(typeid(T))) {
      auto* type_object = (PyTypeObject*)ftype->get().type_object();
      if (PyObject_TypeCheck(obj, type_object)) {
        return handle<T>(obj, mod);
      } else if (auto init = ftype->get().initialiser()) {
        auto* cast_object = PyType_GenericAlloc(type_object, 0);
        if (cast_object != nullptr) {
          std::array<PyObject*, 2> args{cast_object, obj};
          if (init->get().internal_call(args.data(), 2, mod, true)) {
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
  handle<T>::operator T*() { return &bit_cast<pod<T>*>(_obj)->value; }
  template <typename T>
  handle<T>::operator T() const { return bit_cast<pod<T>*>(_obj)->value; }
  template <typename T>
  handle<T>::operator T&() { return bit_cast<pod<T>*>(_obj)->value; }

  template <typename T>
  PyObject* handle<T>::object() { return _obj; }
}

#endif  // INCLUDE_LIGO_IMPL_HANDLE_TPP_
