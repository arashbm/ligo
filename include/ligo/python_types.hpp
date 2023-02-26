#ifndef INCLUDE_LIGO_PYTHON_TYPES_HPP_
#define INCLUDE_LIGO_PYTHON_TYPES_HPP_

#define PY_SSIZE_T_CLEAN
#include <Python.h>

#include <vector>
#include <string>
#include <unordered_map>

#include "python_methods.hpp"

namespace ligo {
  class python_module;

  template <typename T>
  struct pod {
    PyObject_HEAD
    T value;
  };

  int default_init(PyObject*, PyObject*, PyObject*);

  template <typename T>
  class python_type {
  public:
    python_type(const std::string& name, const std::string& docs);

    void add_overload_set(const overload_set& set);

    std::string name() const;
    std::string docs() const;
    std::unordered_map<std::string, overload_set> overload_sets() const;
  private:
    std::string _name;
    std::string _docs;
    std::unordered_map<std::string, overload_set> _overload_sets;
  };

  class final_python_type {
  public:
    template <typename T>
    final_python_type(const python_type<T>& ptype, const std::string& m_name);

    [[nodiscard]] std::string name() const;
    [[nodiscard]] std::string docs() const;
    PyObject* type_object();
    bool init(PyObject* module_instance, python_module& mod);
    std::optional<std::reference_wrapper<overload_set>> initialiser();
  private:
    std::string _name;
    std::string _full_name;
    std::string _docs;
    PyObject* _type_object;
    std::vector<overload_set> _overload_sets;
    std::optional<std::reference_wrapper<overload_set>> _initialiser;
  };
}  // namespace ligo

#endif  // INCLUDE_LIGO_PYTHON_TYPES_HPP_
