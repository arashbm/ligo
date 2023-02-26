#include "../include/ligo/python_methods.hpp"
#include "../include/ligo/impl/python_methods.tpp"

#include <unordered_set>

namespace ligo {
  python_exception::python_exception()
    : runtime_error("a python error occured.") {}
  python_exception::python_exception(const char* what) : runtime_error(what) {}

  overload_set::overload_set(const std::string& name) : _name{name} {
    const std::unordered_set<std::string> operators{
      "__lt__",
      "__le__",
      "__eq__",
      "__ne__",
      "__ge__",
      "__gt__",
    };

    _is_operator = operators.contains(name);
  }

  PyObject* overload_set::operator()(
      PyObject* const* args,
      std::size_t nargs, PyObject* kwnames, python_module& mod) {
    for (auto& [implicit, f]: _overloads)
      if (auto res = f(args, nargs, kwnames, mod, false))
        return *res;

    for (auto& [implicit, f]: _overloads)
      if (auto res = f(args, nargs, kwnames, mod, true))
        return *res;

    if (_is_operator)
      Py_RETURN_NOTIMPLEMENTED;

    return PyErr_Format(PyExc_TypeError,
        "no good overload for these arguments");
  }

  std::optional<PyObject*> overload_set::internal_call(
      PyObject* const* args, std::size_t nargs, python_module& mod,
      bool already_casting) {
    for (auto& [implicit, f]: _overloads)
      if (!already_casting || (already_casting && implicit))
        if (auto res = f(args, nargs, nullptr, mod, false))
          return res;

    if (!already_casting)
      for (auto& [implicit, f]: _overloads)
        if (!already_casting || (already_casting && implicit))
          if (auto res = f(args, nargs, nullptr, mod, true))
            return res;

    return {};
  }

  std::string overload_set::name() const {
    return _name;
  }

  PyObject* method_descriptor_get(
      method_descriptor* descr, PyObject* obj, PyObject* /* obj_type */) {
    if (obj != nullptr) {
      auto* bmeth = PyType_GenericAlloc(&bound_method_definition, 0);
      if (bmeth == nullptr)
        return PyErr_NoMemory();
      std::bit_cast<bound_method*>(bmeth)->set = descr->set;
      std::bit_cast<bound_method*>(bmeth)->mod = descr->mod;
      Py_INCREF(obj);
      std::bit_cast<bound_method*>(bmeth)->obj = obj;
      std::bit_cast<bound_method*>(bmeth)->vectorcall =
        (vectorcallfunc)bound_method_vectorcall;
      Py_INCREF(bmeth);
      return bmeth;
    } else {
      Py_INCREF((PyObject*)descr);
      return (PyObject*)descr;
    }
  }

  PyObject* method_descriptor_vectorcall(
      method_descriptor* descr, PyObject* const* args,
      std::size_t nargs, PyObject* kwnames) {
    overload_set& set = *(descr->set);
    python_module& mod = *(descr->mod);
    return set(args, nargs, kwnames, mod);
  }

  PyObject* bound_method_vectorcall(
      bound_method* bmethod, PyObject* const* args,
      std::size_t nargs, PyObject* kwnames) {
    PyObject* real_self = bmethod->obj;
    overload_set& set = *(bmethod->set);
    python_module& mod = *(bmethod->mod);

    PyObject* res = nullptr;
    if (PY_VECTORCALL_ARGUMENTS_OFFSET & nargs) {
      auto* tmp_args = (PyObject**)args - 1;
      auto* original_arg_zero = tmp_args[0];
      tmp_args[0] = real_self;
      res = set(tmp_args, PyVectorcall_NARGS(nargs) + 1, kwnames, mod);
      tmp_args[0] = original_arg_zero;
    } else {
      std::size_t total_len = PyVectorcall_NARGS(nargs);
      if (kwnames != nullptr)
        total_len += static_cast<std::size_t>(PyObject_Length(kwnames));

      auto* tmp_args = static_cast<PyObject**>(
          PyObject_Malloc((total_len + 1)*sizeof(PyObject*)));
      if (tmp_args == nullptr)
        return PyErr_NoMemory();
      tmp_args[0] = real_self;
      for (size_t i{}; i < total_len; i++)
        tmp_args[i + 1] = args[i];
      res = set(tmp_args, PyVectorcall_NARGS(nargs) + 1, kwnames, mod);
      PyObject_Free(tmp_args);
    }

    return res;
  }

  int bound_method_new(
      bound_method* self, PyObject* args, PyObject* kwds) {
    PyObject* method_desc = nullptr;
    PyObject* obj = nullptr;
    if (!PyArg_ParseTupleAndKeywords(
          args, kwds, "O", nullptr, &method_desc, &obj))
      return -1;

    if (!PyObject_TypeCheck(method_desc, &method_descriptor_definition)) {
      PyErr_SetString(PyExc_TypeError,
          "bound method only accepts a method descriptor argument.");
      return -1;
    }

    auto* mdesc = std::bit_cast<method_descriptor*>(method_desc);

    PyObject* prev_obj = self->obj;
    Py_INCREF(obj);
    self->obj = obj;
    Py_XDECREF(prev_obj);

    self->set = mdesc->set;
    self->mod = mdesc->mod;
    self->vectorcall = (vectorcallfunc)bound_method_vectorcall;

    return 0;
  }

  void set_error_based_on_exception(const std::exception_ptr& exception) {
    try {
      std::rethrow_exception(exception);
    } catch (const python_exception& e) {
      // error is already set
    } catch (const std::bad_alloc& e) {
      PyErr_Format(PyExc_MemoryError, e.what());
    } catch (const std::domain_error& e) {
      PyErr_Format(PyExc_ValueError, e.what());
    } catch (const std::invalid_argument& e) {
      PyErr_Format(PyExc_ValueError, e.what());
    } catch (const std::length_error& e) {
      PyErr_Format(PyExc_ValueError, e.what());
    } catch (const std::out_of_range& e) {
      PyErr_Format(PyExc_IndexError, e.what());
    } catch (const std::range_error& e) {
      PyErr_Format(PyExc_ValueError, e.what());
    } catch (const std::overflow_error& e) {
      PyErr_Format(PyExc_OverflowError, e.what());
    } catch (const std::exception& e) {
      PyErr_Format(PyExc_RuntimeError, e.what());
    } catch (...) {
      PyErr_Format(PyExc_RuntimeError, "Unknown exception");
    }
  }

}
