#include <bit>

#include "../include/ligo/python_module.hpp"
#include "../include/ligo/impl/python_module.tpp"

#include "../include/ligo/python_types.hpp"

namespace ligo {
  python_module::python_module(
      const std::string& name, const std::string& docs) noexcept
    : _name{name}, _docs{docs}, _definition{} {}

  std::string python_module::name() const {
    return _name;
  }

  std::string python_module::docs() const {
    return _docs;
  }

  void python_module::add_overload_set(const overload_set& set) {
    _methods.push_back(set);
  }

  PyObject* python_module::init() {
    _definition = {
      .m_base = PyModuleDef_HEAD_INIT,
      .m_name = _name.c_str(),
      .m_doc = PyDoc_STR(_docs.c_str()),
      .m_size = -1,
      .m_methods = nullptr,
    };

    auto* mod = PyModule_Create(&_definition);
    if (mod == nullptr)
      return nullptr;

    // add internal types
    if (PyType_Ready(&bound_method_definition) < 0)
      return nullptr;
    Py_INCREF(&bound_method_definition);
    if (PyModule_AddObject(mod, "_bound_method",
          std::bit_cast<PyObject*>(&bound_method_definition)) < 0) {
      Py_DECREF(&bound_method_definition);
      Py_DECREF(mod);
      return nullptr;
    }

    if (PyType_Ready(&method_descriptor_definition) < 0)
      return nullptr;
    Py_INCREF(&method_descriptor_definition);
    if (PyModule_AddObject(mod, "_method_descriptor",
          std::bit_cast<PyObject*>(&method_descriptor_definition)) < 0) {
      Py_DECREF(&method_descriptor_definition);
      Py_DECREF(mod);
      return nullptr;
    }

    // add methods
    for (auto& set: _methods) {
      auto* mdesc = PyType_GenericAlloc(&method_descriptor_definition, 0);
      if (mdesc == nullptr)
        return nullptr;

      std::bit_cast<method_descriptor*>(mdesc)->set = &set;
      std::bit_cast<method_descriptor*>(mdesc)->mod = this;
      std::bit_cast<method_descriptor*>(mdesc)->vectorcall =
        (vectorcallfunc)method_descriptor_vectorcall;

      if (PyModule_AddObject(mod, set.name().c_str(), mdesc) < 0) {
        Py_DECREF(mdesc);
        Py_DECREF(mod);
        return nullptr;
      }
    }

    // add defined types
    for (auto& [tindex, final_type]: _types)
      if (!final_type.init(mod, *this))
        return nullptr;

    return mod;
  }

  std::optional<std::reference_wrapper<final_python_type>>
  python_module::final_type(const std::type_index& type_idx) {
    auto ftype = _types.find(type_idx);
    if (ftype == _types.end())
      return {};
    else
      return ftype->second;
  }
}  // namespace ligo
