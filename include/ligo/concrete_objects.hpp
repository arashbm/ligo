#ifndef INCLUDE_LIGO_CONCRETE_OBJECTS_HPP_
#define INCLUDE_LIGO_CONCRETE_OBJECTS_HPP_

#include "python.hpp"

#include <optional>

#include "handle.hpp"

#define LIGO_SPECIALISE_CONCRETE_HANDLE(python_concrete)  \
  template <>                                             \
  class handle<python_concrete> {                         \
  public:                                                 \
    handle(PyObject* obj, python_module& mod);            \
                                                          \
    static std::optional<handle<python_concrete>>         \
    from_cpp(const python_concrete& cpp_obj,              \
        python_module& mod);                              \
                                                          \
    static std::optional<handle<python_concrete>>         \
    from_python(PyObject* obj, python_module& mod);       \
                                                          \
    static std::optional<handle<python_concrete>>         \
    from_python_with_casting(                             \
        PyObject* obj, python_module& mod,                \
        temporary_list& temp_list);                       \
                                                          \
    explicit operator python_concrete*();                 \
    explicit operator python_concrete() const;            \
    explicit operator python_concrete&();                 \
                                                          \
    PyObject* object();                                   \
  private:                                                \
    python_concrete _obj;                                 \
  }

namespace ligo {
  class python_none {
  public:
    explicit python_none(PyObject* obj);
    [[nodiscard]] PyObject* object() const;
  };

  LIGO_SPECIALISE_CONCRETE_HANDLE(python_none);

  class python_bool {
  public:
    explicit python_bool(PyObject* obj);
    [[nodiscard]] PyObject* object() const;
  private:
    PyObject* _object;
  };

  LIGO_SPECIALISE_CONCRETE_HANDLE(python_bool);

  class python_long {
  public:
    explicit python_long(PyObject* obj);
    [[nodiscard]] PyObject* object() const;
  private:
    PyObject* _object;
  };

  LIGO_SPECIALISE_CONCRETE_HANDLE(python_long);

  class python_float {
  public:
    explicit python_float(PyObject* obj);
    [[nodiscard]] PyObject* object() const;
  private:
    PyObject* _object;
  };

  LIGO_SPECIALISE_CONCRETE_HANDLE(python_float);

  class python_complex {
  public:
    explicit python_complex(PyObject* obj);
    [[nodiscard]] PyObject* object() const;
  private:
    PyObject* _object;
  };

  LIGO_SPECIALISE_CONCRETE_HANDLE(python_complex);

  class python_unicode {
  public:
    explicit python_unicode(PyObject* obj);
    [[nodiscard]] PyObject* object() const;
  private:
    PyObject* _object;
  };

  LIGO_SPECIALISE_CONCRETE_HANDLE(python_unicode);

  class python_tuple {
  public:
    explicit python_tuple(PyObject* obj);
    [[nodiscard]] PyObject* object() const;
  private:
    PyObject* _object;
  };

  LIGO_SPECIALISE_CONCRETE_HANDLE(python_tuple);

  class python_list {
  public:
    explicit python_list(PyObject* obj);
    [[nodiscard]] PyObject* object() const;
  private:
    PyObject* _object;
  };

  LIGO_SPECIALISE_CONCRETE_HANDLE(python_list);

  class python_dictionary {
  public:
    explicit python_dictionary(PyObject* obj);
    [[nodiscard]] PyObject* object() const;
  private:
    PyObject* _object;
  };

  LIGO_SPECIALISE_CONCRETE_HANDLE(python_dictionary);

  class python_set {
  public:
    explicit python_set(PyObject* obj);
    [[nodiscard]] PyObject* object() const;
  private:
    PyObject* _object;
  };

  LIGO_SPECIALISE_CONCRETE_HANDLE(python_set);
}  // namespace ligo

#endif  // INCLUDE_LIGO_CONCRETE_OBJECTS_HPP_
