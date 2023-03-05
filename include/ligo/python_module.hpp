#ifndef INCLUDE_LIGO_PYTHON_MODULE_HPP_
#define INCLUDE_LIGO_PYTHON_MODULE_HPP_

#include "python.hpp"

#include <string>
#include <optional>
#include <unordered_map>
#include <vector>
#include <functional>
#include <typeindex>

#include "python_types.hpp"

namespace ligo {
  class overload_set;

  class python_module {
  public:
    python_module(const std::string& name, const std::string& docs) noexcept;
    explicit python_module(const std::string& name) noexcept;

    template <typename T>
    void add_type(const python_type<T>& ptype);

    void add_overload_set(const overload_set& set);
    template<typename F>
    void overload_method(const std::string& name, F&& func,
      const std::array<std::string, function_traits<F>::arity>& keywords);
    template<typename F>
    void define_method(const std::string& name, F&& func,
      const std::array<std::string, function_traits<F>::arity>& keywords);

    std::optional<std::reference_wrapper<final_python_type>>
    final_type(const std::type_index& type_idx);

    [[nodiscard]] std::string name() const;
    [[nodiscard]] std::string docs() const;
    PyObject* init();
  private:
    std::unordered_map<std::type_index, final_python_type> _types;
    std::unordered_map<std::string, overload_set> _methods;
    std::string _name;
    std::string _docs;

    PyModuleDef _definition;
  };
}  // namespace ligo

#endif  // INCLUDE_LIGO_PYTHON_MODULE_HPP_
