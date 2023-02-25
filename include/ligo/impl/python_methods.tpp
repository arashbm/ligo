#ifndef INCLUDE_LIGO_IMPL_PYTHON_METHODS_TPP_
#define INCLUDE_LIGO_IMPL_PYTHON_METHODS_TPP_

#include <optional>
#include <bit>
#include <type_traits>

#include "../python_methods.hpp"

#include "../handle.hpp"
#include "../python_module.hpp"

namespace ligo {
  template <>
  class handle<bool> {
  public:
    handle(PyObject* o, python_module&) : _o{o} {}

    static std::optional<handle<bool>>
    from_cpp(bool b, python_module& m) {
      return handle<bool>(b ? Py_True : Py_False, m);
    }

    static std::optional<handle<bool>>
    from_python(PyObject* o, python_module& m) {
      if (PyBool_Check(o))
        return handle<bool>(o, m);
      return {};
    }

    static std::optional<handle<bool>>
    from_python_with_casting(
        PyObject* o, python_module& m, temporary_list& temp_list) {
      if (PyBool_Check(o))
        return handle<bool>(o, m);

      auto l = PyObject_IsTrue(o);
      if (l == -1)
        return {};

      auto pybool = (l == 1) ? Py_True : Py_False;
      temp_list.add(pybool);
      return handle<bool>(pybool, m);
    }

    operator bool() const { return _o == Py_True; }
    PyObject* object() { return _o; }
  private:
    PyObject* _o;
  };

  template <>
  class handle<PyObject*> {
  public:
    handle(PyObject* o, python_module&) : _o{o} {}

    static std::optional<handle<PyObject*>>
    from_cpp(PyObject* o, python_module& m) {
      return handle<PyObject*>(o, m);
    }

    static std::optional<handle<PyObject*>>
    from_python(PyObject* o, python_module& m) {
      return handle<PyObject*>(o, m);
    }

    static std::optional<handle<PyObject*>>
    from_python_with_casting(PyObject* o, python_module& m, temporary_list&) {
      return handle<PyObject*>(o, m);
    }

    operator PyObject*() const { return _o; }
    PyObject* object() { return _o; }
  private:
    PyObject* _o;
  };

  template <typename ...Args, std::size_t ...Ns>
  std::optional<std::tuple<Args...>>
  unwrap_args_impl(
      const std::array<PyObject*, sizeof...(Args)>& a,
      python_module& m, bool cast, temporary_list& temp_list,
      std::index_sequence<Ns...>) {
    if (cast) {
      std::tuple t(
          handle<std::remove_cvref_t<Args>>::from_python_with_casting(
            std::get<Ns>(a), m, temp_list)...);
      if ((std::get<Ns>(t) && ...))
        return {{static_cast<Args>(std::get<Ns>(t).value())...}};
    } else {
      std::tuple t(
          handle<std::remove_cvref_t<Args>>::from_python(
            std::get<Ns>(a), m)...);
      if ((std::get<Ns>(t) && ...))
        return {{static_cast<Args>(std::get<Ns>(t).value())...}};
    }

    return {};
  };

  template <typename T>
  struct unwrap_args;

  template <typename ...Args>
  struct unwrap_args<metal::list<Args...>> {
    auto operator()(
        const std::array<PyObject*, sizeof...(Args)>& a,
        python_module& m,
        bool cast, temporary_list& temp_list) {
      return unwrap_args_impl<Args...>(
          a, m, cast, temp_list,
          std::index_sequence_for<Args...>{});
    }
  };

  template<typename F>
  void overload_set::_wrap_and_add(
      F&& f,
      std::array<std::string, function_traits<F>::arity> keywords,
      bool implicit) {
    using traits = function_traits<F>;


    std::unordered_map<std::string, std::size_t> kw_index;
    for (std::size_t i{}; i < traits::arity; i++)
      kw_index[keywords[i]] = i;

    auto impl = [f, kw_index](
        PyObject* const* args, std::size_t nargs,
        PyObject* kwnames, python_module& mod, bool cast)
          -> std::optional<PyObject*> {
      // check total number of arguments
      std::size_t total_args_len = PyVectorcall_NARGS(nargs);
      if (kwnames)
        total_args_len += static_cast<std::size_t>(PyObject_Length(kwnames));
      if (total_args_len != traits::arity)
        return {};

      std::array<PyObject*, traits::arity> py_args;
      for (std::size_t i{}; i < PyVectorcall_NARGS(nargs); i++)
        py_args[i] = args[i];

      if (kwnames) {
        for (std::size_t i{}; i < PyObject_Length(kwnames); i++) {
          auto kw = PyUnicode_AsUTF8String(PyTuple_GetItem(kwnames, i));
          if (!kw)
            return {};
          auto kwstr = PyBytes_AsString(kw);
          if (!kwstr)
            return {};

          auto idx = kw_index.find(kwstr);
          if (idx != kw_index.end())
            py_args[idx->second] = args[i + PyObject_Length(kwnames)];
          else
            return {};  // received an unknown keyword argument
        }
      }

      temporary_list temp_list;
      auto t_args = unwrap_args<typename traits::args>{}(
          py_args, mod, cast, temp_list);
      if (!t_args)
        return {};

      // wrap this in try catch if not noexcept?
      PyObject* res;
      try {
        if constexpr (std::is_void_v<typename traits::result_type>) {
          std::apply(f, *t_args);
          Py_RETURN_NONE;
        } else {
          if (auto p = handle<
              std::remove_cvref_t<typename traits::result_type>>::from_cpp(
                std::apply(f, *t_args), mod))
            return p->object();
          else
            return PyErr_Format(PyExc_TypeError,
                "could not convert the return type to Python objects");
        }
      } catch (const python_exception& e) {
        return (PyObject*)nullptr; // error is already set
      } catch (const std::bad_alloc& e) {
        return PyErr_Format(PyExc_MemoryError, e.what());
      } catch (const std::domain_error& e) {
        return PyErr_Format(PyExc_ValueError, e.what());
      } catch (const std::invalid_argument& e) {
        return PyErr_Format(PyExc_ValueError, e.what());
      } catch (const std::length_error& e) {
        return PyErr_Format(PyExc_ValueError, e.what());
      } catch (const std::out_of_range& e) {
        return PyErr_Format(PyExc_IndexError, e.what());
      } catch (const std::range_error& e) {
        return PyErr_Format(PyExc_ValueError, e.what());
      } catch (const std::overflow_error& e) {
        return PyErr_Format(PyExc_OverflowError, e.what());
      } catch (const std::exception& e) {
        return PyErr_Format(PyExc_RuntimeError, e.what());
      } catch (...) {
        std::exception_ptr p = std::current_exception();
        return PyErr_Format(PyExc_RuntimeError, "Unknown exception");
      }
    };

    _overloads.emplace_back(implicit, impl);
  }

  template<typename F>
  void overload_set::add_overload(F&& f,
      std::array<std::string, function_traits<F>::arity> keywords) {
    _wrap_and_add(std::forward<F>(f),
        std::forward<decltype(keywords)>(keywords), false);
  }

  template<typename F>
  void overload_set::add_implicit_overload(F&& f,
      std::array<std::string, function_traits<F>::arity> keywords) {
    if (_name != "__init__")
      throw std::logic_error(
          "methods other than the initiliser cannot be implicit");

    _wrap_and_add(std::forward<F>(f),
        std::forward<decltype(keywords)>(keywords), true);
  }
}  // namespace ligo

#endif  // INCLUDE_LIGO_IMPL_PYTHON_METHODS_TPP_
