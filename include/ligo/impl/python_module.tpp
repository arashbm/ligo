#ifndef INCLUDE_LIGO_IMPL_PYTHON_MODULE_TPP_
#define INCLUDE_LIGO_IMPL_PYTHON_MODULE_TPP_

#include "../include/ligo/python_module.hpp"
#include "../include/ligo/python_methods.hpp"

#include <utility>
#include <tuple>

namespace ligo {
  template <typename T>
  void python_module::add_type(const python_type<T>& ptype) {
    _types.emplace(
        std::piecewise_construct,
        std::forward_as_tuple(typeid(T)),
        std::forward_as_tuple(ptype, _name));
  }

  template<typename F, typename ...Guards>
  void python_module::overload_method(
      const std::string& name, F&& func,
      const overload_set::args_tuple<F>& args,
      call_gurad<Guards...> guards) {
    auto iter = _methods.find(name);
    if (iter != _methods.end()) {
      iter->second.add_overload(
        std::forward<F>(func), args, guards);
    } else {
      overload_set set(name);
      set.add_overload(std::forward<F>(func), args, guards);
      _methods.insert({name, set});
    }
  }

  template<typename F, typename ...Guards>
  void python_module::define_method(
      const std::string& name, F&& func,
      const overload_set::args_tuple<F>& args,
      call_gurad<Guards...> guards) {
    overload_set set(name);
    set.add_overload(std::forward<F>(func), args, guards);
    _methods.insert_or_assign(name, set);
  }
}  // namespace ligo

#endif  // INCLUDE_LIGO_IMPL_PYTHON_MODULE_TPP_
