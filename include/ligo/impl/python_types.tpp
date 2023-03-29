#ifndef INCLUDE_LIGO_IMPL_PYTHON_TYPES_TPP_
#define INCLUDE_LIGO_IMPL_PYTHON_TYPES_TPP_

#include <array>

#include <fmt/format.h>

#include "../python_types.hpp"

namespace ligo {
  template <typename T>
  python_type<T>::python_type(const std::string& name, const std::string& docs)
      : _name{name}, _docs{docs} {};

  template <typename T>
  void python_type<T>::add_overload_set(const overload_set& set) {
    _overload_sets.emplace(set.name(), set);
  }

  template <typename T>
  template<typename F, typename ...Guards>
  void python_type<T>::overload_method(
      const std::string& name, F&& func,
      const overload_set::args_tuple<F>& args,
      call_guard<Guards...> guards) {
    auto iter = _overload_sets.find(name);
    if (iter != _overload_sets.end()) {
      iter->second.add_overload(
        std::forward<F>(func), args, guards);
    } else {
      overload_set set(name);
      set.add_overload(std::forward<F>(func), args, guards);
      _overload_sets.insert({name, set});
    }
  }

  template <typename T>
  template<typename F, typename ...Guards>
  void python_type<T>::implicit_overload_method(
      const std::string& name, F&& func,
      const overload_set::args_tuple<F>& args,
      call_guard<Guards...> guards) {
    auto iter = _overload_sets.find(name);
    if (iter != _overload_sets.end()) {
      iter->second.add_implicit_overload(
        std::forward<F>(func), args, guards);
    } else {
      overload_set set(name);
      set.add_implicit_overload(std::forward<F>(func), args, guards);
      _overload_sets.insert({name, set});
    }
  }

  template <typename T>
  template<typename F, typename ...Guards>
  void python_type<T>::define_method(
      const std::string& name, F&& func,
      const overload_set::args_tuple<F>& args,
      call_guard<Guards...> guards) {
    overload_set set(name);
    set.add_overload(std::forward<F>(func), args, guards);
    _overload_sets.insert_or_assign(name, set);
  }

  template <typename T>
  template<typename F, typename ...Guards>
  void python_type<T>::implicit_define_method(
      const std::string& name, F&& func,
      const overload_set::args_tuple<F>& args,
      call_guard<Guards...> guards) {
    overload_set set(name);
    set.add_implicit_overload(std::forward<F>(func), args, guards);
    _overload_sets.insert_or_assign(name, set);
  }

  template <typename T>
  std::string python_type<T>::name() const {
    return _name;
  }

  template <typename T>
  std::string python_type<T>::docs() const {
    return _docs;
  }

  template <typename T>
  std::unordered_map<std::string, overload_set>
  python_type<T>::overload_sets() const {
    return _overload_sets;
  }

  template <typename T>
  final_python_type::final_python_type(
        const python_type<T>& ptype, const std::string& m_name) :
      _name{ptype.name()},
      _full_name{fmt::format("{}.{}", m_name, _name)},
      _docs{ptype.docs()} {
    std::array<PyType_Slot, 4> slots{{
      {Py_tp_doc, (void*)PyDoc_STR(_docs.c_str())},
      {Py_tp_init, (void*)(initproc)default_init},
      {Py_tp_new, (void*)PyType_GenericNew},
      {0, nullptr},
    }};

    PyType_Spec specs{
      .name = _full_name.c_str(),
      .basicsize = sizeof(pod<T>),
      .itemsize = 0,
      .flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_HEAPTYPE,
      .slots = slots.data()
    };

    _type_object = PyType_FromSpec(&specs);

    for (auto& [name, os]: ptype.overload_sets())
      _overload_sets.push_back(os);
  };
}

#endif  // INCLUDE_LIGO_IMPL_PYTHON_TYPES_TPP_
