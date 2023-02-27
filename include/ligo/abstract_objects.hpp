#ifndef INCLUDE_LIGO_ABSTRACT_OBJECTS_HPP_
#define INCLUDE_LIGO_ABSTRACT_OBJECTS_HPP_

#include "python.hpp"

#include <optional>

#include "handle.hpp"

#define LIGO_SPECIALISE_ABSTRACT_HANDLE(python_abstract)  \
  template <>                                             \
  class handle<python_abstract> {                         \
  public:                                                 \
    handle(PyObject* obj, python_module& mod);            \
                                                          \
    static std::optional<handle<python_abstract>>         \
    from_cpp(const python_abstract& cpp_obj,              \
        python_module& mod);                              \
                                                          \
    static std::optional<handle<python_abstract>>         \
    from_python(PyObject* obj, python_module& mod);       \
                                                          \
    static std::optional<handle<python_abstract>>         \
    from_python_with_casting(                             \
        PyObject* obj, python_module& mod,                \
        temporary_list& tmp_list);                        \
                                                          \
    operator python_abstract*();                          \
    operator python_abstract() const;                     \
    operator python_abstract&();                          \
                                                          \
    PyObject* object();                                   \
  private:                                                \
    python_abstract _obj;                                 \
  }


namespace ligo {
  class python_object {
  public:
    explicit python_object(PyObject* obj);
    [[nodiscard]] PyObject* object() const;
  private:
    PyObject* _object;
  };

  LIGO_SPECIALISE_ABSTRACT_HANDLE(python_object);

  class python_callable {
  public:
    explicit python_callable(PyObject* obj);
    [[nodiscard]] PyObject* object() const;
  private:
    PyObject* _object;
  };

  LIGO_SPECIALISE_ABSTRACT_HANDLE(python_callable);

  class python_number {
  public:
    explicit python_number(PyObject* obj);
    [[nodiscard]] PyObject* object() const;
  private:
    PyObject* _object;
  };

  LIGO_SPECIALISE_ABSTRACT_HANDLE(python_number);

  class python_index {
  public:
    explicit python_index(PyObject* obj);
    [[nodiscard]] PyObject* object() const;
  private:
    PyObject* _object;
  };

  LIGO_SPECIALISE_ABSTRACT_HANDLE(python_index);

  class python_sequence {
  public:
    explicit python_sequence(PyObject* obj);
    [[nodiscard]] PyObject* object() const;
  private:
    PyObject* _object;
  };

  LIGO_SPECIALISE_ABSTRACT_HANDLE(python_sequence);

  class python_mapping {
  public:
    explicit python_mapping(PyObject* obj);
    [[nodiscard]] PyObject* object() const;
  private:
    PyObject* _object;
  };

  LIGO_SPECIALISE_ABSTRACT_HANDLE(python_mapping);

  class python_iterator {
  public:
    explicit python_iterator(PyObject* obj);
    [[nodiscard]] PyObject* object() const;
  private:
    PyObject* _object;
  };

  LIGO_SPECIALISE_ABSTRACT_HANDLE(python_iterator);

  class python_buffer {
  public:
    explicit python_buffer(PyObject* obj);
    [[nodiscard]] PyObject* object() const;
  private:
    PyObject* _object;
  };

  LIGO_SPECIALISE_ABSTRACT_HANDLE(python_buffer);
}  // namespace ligo

#endif  // INCLUDE_LIGO_ABSTRACT_OBJECTS_HPP_
