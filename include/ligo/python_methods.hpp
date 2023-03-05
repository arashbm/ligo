#ifndef INCLUDE_LIGO_PYTHON_METHODS_HPP_
#define INCLUDE_LIGO_PYTHON_METHODS_HPP_

#include "python.hpp"

#include <concepts>
#include <functional>
#include <optional>
#include <string>
#include <stdexcept>
#include <unordered_map>

#include "metal.hpp"

#include "utils.hpp"
#include "abstract_objects.hpp"
#include "concrete_objects.hpp"

namespace ligo {
  class python_module;

  struct python_exception : public std::runtime_error {
    python_exception();
    explicit python_exception(const char* what);
  };

  class overload_set {
  public:
    using wrapped_function = std::optional<PyObject*>(
        PyObject* const*, std::size_t, PyObject*, python_module&, bool);

    explicit overload_set(const std::string& name);

    template<typename F>
    void add_overload(F&& func,
      const std::array<std::string, function_traits<F>::arity>& keywords);

    template<typename F>
    void add_implicit_overload(F&& func,
      const std::array<std::string, function_traits<F>::arity>& keywords);

    PyObject* operator()(PyObject* const* args,
        std::size_t nargs, PyObject* kwnames, python_module& mod);

    std::optional<PyObject*> internal_call(PyObject* const* args,
        std::size_t nargs, python_module& mod, bool already_casting);

    [[nodiscard]] std::string name() const;
  private:
    template<typename F>
    void _wrap_and_add(
        F&& func,
        const std::array<std::string, function_traits<F>::arity>& keywords,
        bool implicit);
    std::string _name;
    bool _is_operator;
    std::vector<std::pair<bool, std::function<wrapped_function>>> _overloads;
  };

  struct method_descriptor {
    PyObject_HEAD
    overload_set* set;
    python_module* mod;
    vectorcallfunc vectorcall;
  };

  PyObject* method_descriptor_get(
      method_descriptor* descr, PyObject* obj, PyObject* obj_type);

  PyObject* method_descriptor_vectorcall(
      method_descriptor* descr, PyObject* const* args,
      std::size_t nargs, PyObject* kwnames);

  static PyTypeObject method_descriptor_definition = {
    .ob_base = PyVarObject_HEAD_INIT(nullptr, 0)
    .tp_name = "ligo.method_descriptor",
    .tp_basicsize = sizeof(method_descriptor),
    .tp_itemsize = 0,
    .tp_vectorcall_offset = offsetof(method_descriptor, vectorcall),
    .tp_call = PyVectorcall_Call,
    .tp_flags =
      Py_TPFLAGS_DEFAULT |
      Py_TPFLAGS_METHOD_DESCRIPTOR |
      Py_TPFLAGS_HAVE_VECTORCALL,
    .tp_doc = PyDoc_STR("method descriptor"),
    .tp_descr_get = (descrgetfunc)method_descriptor_get,
  };

  struct bound_method {
    PyObject_HEAD
    PyObject* obj;
    overload_set* set;
    python_module* mod;
    vectorcallfunc vectorcall;
  };

  PyObject* bound_method_vectorcall(
      bound_method* bmethod, PyObject* const* args,
      std::size_t nargs, PyObject* kwnames);

  int bound_method_new(
      bound_method* self, PyObject* args, PyObject* kwds);

  static PyTypeObject bound_method_definition = {
    .ob_base = PyVarObject_HEAD_INIT(nullptr, 0)
    .tp_name = "ligo.bound_method",
    .tp_basicsize = sizeof(bound_method),
    .tp_itemsize = 0,
    .tp_vectorcall_offset = offsetof(bound_method, vectorcall),
    .tp_call = PyVectorcall_Call,
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_HAVE_VECTORCALL,
    .tp_doc = PyDoc_STR("bound method callable"),
    .tp_new = PyType_GenericNew,
  };

  void set_error_based_on_exception(const std::exception_ptr& exception);
}

#endif  // INCLUDE_LIGO_PYTHON_METHODS_HPP_
