#ifndef INCLUDE_LIGO_IMPL_PYTHON_METHODS_TPP_
#define INCLUDE_LIGO_IMPL_PYTHON_METHODS_TPP_

#include <iostream>

#include <cstddef>
#include <iterator>
#include <optional>
#include <bit>
#include <string>
#include <tuple>
#include <type_traits>
#include <utility>

#include "../python_methods.hpp"

#include "../handle.hpp"
#include "../python_module.hpp"
#include "ligo/utils.hpp"

namespace ligo {
  template <>
  class handle<bool> {
  public:
    handle(PyObject* obj, python_module& /* mod */) : _obj{obj} {}

    static std::optional<handle<bool>>
    from_cpp(bool value, python_module& mod) {
      return handle<bool>(value ? Py_True : Py_False, mod);
    }

    static std::optional<handle<bool>>
    from_python(PyObject* obj, python_module& mod) {
      if (PyBool_Check(obj))
        return handle<bool>(obj, mod);
      return {};
    }

    static std::optional<handle<bool>>
    from_python_with_casting(
        PyObject* obj, python_module& mod, temporary_list& tmp_list) {
      if (PyBool_Check(obj))
        return handle<bool>(obj, mod);

      int truthiness = PyObject_IsTrue(obj);
      if (truthiness == -1)
        return {};

      auto* pybool = (truthiness == 1) ? Py_True : Py_False;
      tmp_list.add(pybool);
      return handle<bool>(pybool, mod);
    }

    explicit operator bool() const { return _obj == Py_True; }
    PyObject* object() { return _obj; }
  private:
    PyObject* _obj;
  };

  template <>
  class handle<PyObject*> {
  public:
    handle(PyObject* obj, python_module& /* mod */) : _obj{obj} {}

    static std::optional<handle<PyObject*>>
    from_cpp(PyObject* obj, python_module& mod) {
      return handle<PyObject*>(obj, mod);
    }

    static std::optional<handle<PyObject*>>
    from_python(PyObject* obj, python_module& mod) {
      return handle<PyObject*>(obj, mod);
    }

    static std::optional<handle<PyObject*>>
    from_python_with_casting(
        PyObject* obj, python_module& mod, temporary_list& /* tmp_list */) {
      return handle<PyObject*>(obj, mod);
    }

    explicit operator PyObject*() const { return _obj; }
    PyObject* object() { return _obj; }
  private:
    PyObject* _obj;
  };

  template <typename ...ArgTypes, typename ...ArgDefs, std::size_t ...Ns>
  std::optional<std::tuple<ArgTypes...>>
  unwrap_args_impl(
      const std::array<PyObject*, sizeof...(ArgTypes)>& args_array,
      python_module& mod, bool cast, temporary_list& tmp_list,
      const std::tuple<ArgDefs...>& arg_defs,
      std::index_sequence<Ns...> /* is */) {

    auto get_arg = [&]<std::size_t idx, typename ArgType>()
        -> std::optional<handle<std::remove_cvref_t<ArgType>>>{
      auto arg_definition = std::get<idx>(arg_defs);
      auto arg = std::get<idx>(args_array);
      if (arg != nullptr && cast && arg_definition.convert)
        return handle<std::remove_cvref_t<ArgType>>::from_python_with_casting(
          arg, mod, tmp_list);
      else if (arg != nullptr)
        return handle<std::remove_cvref_t<ArgType>>::from_python(arg, mod);
      else if (arg == nullptr && arg_definition.default_value.has_value())
        return handle<std::remove_cvref_t<ArgType>>::from_cpp(
            arg_definition.default_value.value(), mod);
      else
        return {};
    };

    std::tuple args_tpl(get_arg.template operator()<Ns, ArgTypes>()...);
    if ((std::get<Ns>(args_tpl) && ...))
      return {{static_cast<ArgTypes>(std::get<Ns>(args_tpl).value())...}};

    return {};
  };

  template <typename T1, typename T2>
  struct unwrap_args;

  template <typename ...ArgTypes, typename ...ArgDefs>
  struct unwrap_args<metal::list<ArgTypes...>, std::tuple<ArgDefs...>> {
    auto operator()(
        const std::array<PyObject*, sizeof...(ArgTypes)>& args_array,
        python_module& mod,
        bool cast, temporary_list& tmp_list,
        const std::tuple<ArgDefs...>& arg_defs) {
      return unwrap_args_impl<ArgTypes...>(
          args_array, mod, cast, tmp_list, arg_defs,
          std::index_sequence_for<ArgTypes...>{});
    }
  };

  template<typename ...Args, size_t ...Is>
  std::unordered_map<std::string, std::size_t>
  _keyword_indecies_impl(
      const std::tuple<Args...>& args,
      std::index_sequence<Is...> /* is */) {
    std::unordered_map<std::string, std::size_t> kw_index;
    (kw_index.emplace(std::get<Is>(args).name, Is), ...);

    return kw_index;
  }

  template<typename ...Args>
  std::unordered_map<std::string, std::size_t>
  _keyword_indecies(const std::tuple<Args...>& args) {
    return _keyword_indecies_impl(args, std::index_sequence_for<Args...>());
  }


  template <typename ...Args, std::size_t ...Is>
  std::size_t _mandatory_args_impl(
      const std::tuple<Args...>& args,
      std::index_sequence<Is...> /* is */) {
    std::size_t result = sizeof...(Is); 
    bool found = false;
    auto check_pred = [&]<std::size_t idx>(){
      if (!found && std::get<idx>(args).default_value) {
        result = idx;
        found = true;
      } else if (found && !std::get<idx>(args).default_value) {
        throw std::logic_error("non-default argument follows default argument");
      }
    };

    (check_pred.template operator()<Is>(), ...);

    return result;
  }
  
  template <typename ...Args>
  std::size_t _mandatory_args(const std::tuple<Args...>& args) {
    return _mandatory_args_impl(args, std::index_sequence_for<Args...>{});
  }

  template<typename F>
  std::optional<std::array<PyObject*, function_traits<F>::arity>>
  _ordered_arguments(
    PyObject* const* args, std::size_t nargs, PyObject* kwnames,
    const std::unordered_map<std::string, std::size_t>& kw_index,
    std::size_t mandatory_args) {
    std::size_t positional_args_len = PyVectorcall_NARGS(nargs);
    std::size_t total_args_len = positional_args_len;
    std::size_t kw_length = 0;

    if (kwnames != nullptr)
      kw_length = static_cast<std::size_t>(PyObject_Length(kwnames));
    total_args_len += kw_length;

    if (total_args_len < mandatory_args || total_args_len > function_traits<F>::arity)
      return {};

    std::array<PyObject*, function_traits<F>::arity> py_args{};
    for (std::size_t i{}; i < positional_args_len; i++)
      py_args.at(i) = args[i];

    if (kw_length > 0) {
      for (ptrdiff_t i{}; i < static_cast<ptrdiff_t>(kw_length); i++) {
        const auto* kwstr = PyUnicode_AsUTF8(PyTuple_GetItem(kwnames, i));
        if (!kwstr)
          return {};

        auto idx = kw_index.find(kwstr);
        if (idx != kw_index.end())
          py_args.at(idx->second) = args[i + kw_length];
        else
          return {};  // received an unknown keyword argument
      }
    }
    return py_args;
  }

  template<typename F, typename ...Guards>
  void overload_set::_wrap_and_add(
      F&& func,
      const overload_set::args_tuple<F>& args,
      call_guard<Guards...> /* guards */,
      bool implicit) {
    using traits = function_traits<F>;
    auto kw_index = _keyword_indecies(args);
    std::size_t mandatory_args = _mandatory_args(args);
    auto impl = [func, kw_index, mandatory_args, args](
        PyObject* const* given_args, std::size_t nargs,
        PyObject* kwnames, python_module& mod, bool cast)
          -> std::optional<PyObject*> {
      auto py_args = _ordered_arguments<F>(
          given_args, nargs, kwnames, kw_index, mandatory_args);
      if (!py_args)
        return {};

      temporary_list tmp_list;
      auto t_args = unwrap_args<
        typename traits::args, overload_set::args_tuple<F>>{}(
          *py_args, mod, cast, tmp_list, args);
      if (!t_args)
        return {};

      // wrap this in try catch if not noexcept?
      PyObject* res = nullptr;
      try {
        if constexpr (std::is_void_v<typename traits::result_type>) {
          [&func, &t_args](){
            std::tuple<Guards...> grds{};
            std::apply(func, *t_args);
          }();
          Py_RETURN_NONE;
        } else {
          if (auto return_val_handle = handle<
              std::remove_cvref_t<typename traits::result_type>>::from_cpp(
                [&func, &t_args](){
                  std::tuple<Guards...> grds{};
                  return std::apply(func, *t_args);
                }(), mod))
            return return_val_handle->object();
          else
            return PyErr_Format(PyExc_TypeError,
                "could not convert the return type to Python objects");
        }
      } catch (...) {
        std::exception_ptr current_exception = std::current_exception();
        set_error_based_on_exception(current_exception);
        return (PyObject*)nullptr;
      }
    };

    _overloads.push_back({implicit, impl});
  }

  template<typename F, typename ...Guards>
  void overload_set::add_overload(
      F&& func, const overload_set::args_tuple<F>& args,
      call_guard<Guards...> guards) {
    _wrap_and_add(std::forward<F>(func), args, guards, false);
  }

  template<typename F, typename ...Guards>
  void overload_set::add_implicit_overload(
      F&& func, const overload_set::args_tuple<F>& args,
      call_guard<Guards...> guards) {
    if (_name != "__init__")
      throw std::logic_error(
          "methods other than the initiliser cannot be implicit");
    _wrap_and_add(std::forward<F>(func), args, guards, true);
  }
}  // namespace ligo

#endif  // INCLUDE_LIGO_IMPL_PYTHON_METHODS_TPP_
