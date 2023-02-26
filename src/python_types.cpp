#include <bit>

#include "../include/ligo/python_types.hpp"

namespace ligo {
  std::string final_python_type::name() const {
    return _name;
  }

  std::string final_python_type::docs() const {
    return _docs;
  }

  PyObject* final_python_type::type_object() {
    return _type_object;
  }

  std::optional<std::reference_wrapper<overload_set>>
  final_python_type::initialiser() {
    return _initialiser;
  }

  bool final_python_type::init(PyObject* module_instance, python_module& mod) {
    Py_INCREF(_type_object);
    if (PyModule_AddObject(
          module_instance, _name.c_str(), _type_object) < 0) {
      Py_DECREF(_type_object);
      Py_DECREF(module_instance);
      return false;
    }

    // add method descriptors
    for (auto& set: _overload_sets) {
      if (set.name() == "__init__")
        _initialiser = std::ref(set);


      auto* mdesc = PyType_GenericAlloc(&method_descriptor_definition, 0);
      if (mdesc == nullptr)
        return false;

      std::bit_cast<method_descriptor*>(mdesc)->set = &set;
      std::bit_cast<method_descriptor*>(mdesc)->mod = &mod;
      std::bit_cast<method_descriptor*>(mdesc)->vectorcall =
        (vectorcallfunc)method_descriptor_vectorcall;

      if (PyObject_SetAttrString(_type_object, set.name().c_str(), mdesc) < 0) {
        Py_DECREF(_type_object);
        Py_DECREF(mdesc);
        return false;
      }
    }

    return true;
  }

  int default_init(PyObject* self, PyObject* /* args */, PyObject* /* kwargs */) {
    PyErr_Format(PyExc_TypeError,
        "cannot create new instances of type %R: no constructor defined.",
        Py_TYPE(self));
    return -1;
  }
}
