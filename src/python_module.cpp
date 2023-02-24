#include <bit>

#include "../include/ligo/python_module.hpp"
#include "../include/ligo/impl/python_module.tpp"

#include "../include/ligo/python_types.hpp"

namespace ligo {
  python_module::python_module(
      const std::string& name, const std::string& docs)
    : _name{name}, _docs{docs} {}

  std::string python_module::name() const {
    return _name;
  }

  std::string python_module::docs() const {
    return _docs;
  }

  void python_module::add_overload_set(const overload_set& os) {
    _methods.push_back(os);
  }

  PyObject* python_module::init() {
    _definition = {
      .m_base = PyModuleDef_HEAD_INIT,
      .m_name = _name.c_str(),
      .m_doc = PyDoc_STR(_docs.c_str()),
      .m_size = -1,
      .m_methods = nullptr,
    };

    auto m = PyModule_Create(&_definition);
    if (m == nullptr)
      return nullptr;

    // add internal types
    if (PyType_Ready(&bound_method_definition) < 0)
      return nullptr;
    Py_INCREF(&bound_method_definition);
    if (PyModule_AddObject(m, "_bound_method",
          std::bit_cast<PyObject*>(&bound_method_definition)) < 0) {
      Py_DECREF(&bound_method_definition);
      Py_DECREF(m);
      return nullptr;
    }

    if (PyType_Ready(&method_descriptor_definition) < 0)
      return nullptr;
    Py_INCREF(&method_descriptor_definition);
    if (PyModule_AddObject(m, "_method_descriptor",
          std::bit_cast<PyObject*>(&method_descriptor_definition)) < 0) {
      Py_DECREF(&method_descriptor_definition);
      Py_DECREF(m);
      return nullptr;
    }

    // add methods
    for (auto& os: _methods) {
      auto md = PyType_GenericAlloc(&method_descriptor_definition, 0);
      if (md == nullptr)
        return nullptr;

      std::bit_cast<method_descriptor*>(md)->set = &os;
      std::bit_cast<method_descriptor*>(md)->mod = this;
      std::bit_cast<method_descriptor*>(md)->vectorcall =
        (vectorcallfunc)method_descriptor_vectorcall;

      if (PyModule_AddObject(m, os.name().c_str(), md) < 0) {
        Py_DECREF(md);
        Py_DECREF(m);
        return nullptr;
      }
    }

    // add defined types
    for (auto& [tindex, final_type]: _types)
      if (!final_type.init(m, *this))
        return nullptr;

    return m;
  }

  std::optional<std::reference_wrapper<final_python_type>>
  python_module::final_type(const std::type_index& t) {
    auto ft = _types.find(t);
    if (ft == _types.end())
      return {};
    else
      return ft->second;
  }

}  // namespace ligo
