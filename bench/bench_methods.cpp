#include <ligo/ligo.hpp>

class hello {};

LIGO_MODULE(bench_methods_ext, "module for benchmarking methods", mod) {
  ligo::overload_set no_input_set("no_input");
  no_input_set.add_overload([]() -> PyObject* { Py_RETURN_TRUE; }, {});
  mod.add_overload_set(no_input_set);

  ligo::overload_set object_input_set("object_input");
  object_input_set.add_overload(
      [](PyObject* /* obj */) -> PyObject* { Py_RETURN_TRUE; }, {{"obj"}});
  mod.add_overload_set(object_input_set);

  ligo::overload_set multiple_input_set("multiple_object_input");
  multiple_input_set.add_overload(
      [](PyObject* /* a */, PyObject* /* b */, PyObject* /* c */)
        -> PyObject* { Py_RETURN_TRUE; },
      {{"a"}, {"b"}, {"c"}});
  mod.add_overload_set(multiple_input_set);


  ligo::python_type<hello> hlo("hello", "hello test class");
  ligo::overload_set hello_init("__init__");
  hello_init.add_overload([](hello& self) {
      new (&self) hello{};
    }, {{"self"}});
  hlo.add_overload_set(hello_init);
  mod.add_type(hlo);
  
  ligo::overload_set bound_class_input_set("bound_class_input");
  bound_class_input_set.add_overload(
      [](hello /* obj */) -> PyObject* { Py_RETURN_TRUE; }, {{"obj"}});
  mod.add_overload_set(bound_class_input_set);

  ligo::overload_set bound_class_reference_input_set("bound_class_reference_input");
  bound_class_reference_input_set.add_overload(
      [](hello& /* obj */) -> PyObject* { Py_RETURN_TRUE; }, {{"obj"}});
  mod.add_overload_set(bound_class_reference_input_set);
}
