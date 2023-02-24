#include "../include/ligo/handle.hpp"

namespace ligo {
  temporary_list::~temporary_list() {
    for (auto&& obj: _list)
      Py_DECREF(obj);
  }

  void temporary_list::add(PyObject* obj) {
    _list.push_back(obj);
  }
}  // namespace ligo
