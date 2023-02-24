#ifndef INCLUDE_LIGO_IMPL_PYTHON_MODULE_TPP_
#define INCLUDE_LIGO_IMPL_PYTHON_MODULE_TPP_

#include "../include/ligo/python_module.hpp"

#include <utility>
#include <tuple>

namespace ligo {
  template <typename T>
  void python_module::add_type(const python_type<T>& t) {
    _types.emplace(
        std::piecewise_construct,
        std::forward_as_tuple(typeid(T)),
        std::forward_as_tuple(t, _name));
  }
}  // namespace ligo

#endif  // INCLUDE_LIGO_IMPL_PYTHON_MODULE_TPP_
