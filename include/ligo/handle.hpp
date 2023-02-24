#ifndef INCLUDE_LIGO_HANDLE_HPP_
#define INCLUDE_LIGO_HANDLE_HPP_

#define PY_SSIZE_T_CLEAN
#include <Python.h>

#include <optional>
#include <vector>

namespace ligo {
  class python_module;

  class temporary_list {
  public:
    temporary_list() = default;
    temporary_list(temporary_list&) = delete;
    temporary_list(temporary_list&&) = default;
    temporary_list& operator=(const temporary_list&) = delete;
    temporary_list& operator=(temporary_list&&) = default;
    ~temporary_list();
    void add(PyObject* obj);
  private:
    std::vector<PyObject*> _list;
  };


  template <typename T>
  class handle {
  public:
    handle(PyObject* obj, python_module& mod);

    static std::optional<handle>
    from_cpp(const T& value, python_module& mod);
    static std::optional<handle>
    from_python(PyObject* obj, python_module& mod);
    static std::optional<handle>
    from_python_with_casting(
        PyObject* obj, python_module& mod, temporary_list& tmp_list);

    explicit operator T*();
    explicit operator T() const;
    explicit operator T&();
    PyObject* object();
  private:
    PyObject* _obj;
    python_module& _mod;
  };
}  // namespace ligo
#endif  // INCLUDE_LIGO_HANDLE_HPP_
