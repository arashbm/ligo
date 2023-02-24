#include <functional>

#include <ligo/ligo.hpp>

static ligo::python_module mod("libtest_types", "module for testing types");

class hello {
public:
  hello() = default;
  hello(int i) : _i{i} {}

  int func() {
    return _i++;
  }

  int const_func() const {
    return _i;
  }

  int const_noexcept_func() const noexcept {
    return _i;
  }
private:
  int _i;
};

class world {
public:
  world() = default;
  world(const hello&) {}
  hello test_return_hello() {
    return hello(42);
  };
};

PyMODINIT_FUNC PyInit_libtest_types() {
  ligo::python_type<int> int_type("int", "int type");
  ligo::overload_set int_repr("__repr__");
  int_repr.add_overload([](int a){
      return PyUnicode_FromFormat("%i", a);
    }, {"a"});
  int_type.add_overload_set(int_repr);

  ligo::overload_set int_eq("__eq__");
  int_eq.add_overload(std::equal_to<int>{}, {"a", "b"});
  int_type.add_overload_set(int_eq);

  ligo::overload_set int_ne("__ne__");
  int_ne.add_overload(std::not_equal_to<int>{}, {"a", "b"});
  int_type.add_overload_set(int_ne);
  mod.add_type(int_type);

  ligo::python_type<hello> h("hello", "hello test class");
  ligo::overload_set hello_init("__init__");
  hello_init.add_overload([](hello& self) {
      new (&self) hello{};
    }, {"self"});
  h.add_overload_set(hello_init);

  ligo::overload_set hello_lt("__lt__");
  hello_lt.add_overload([](const hello& a, const hello& b) {
      return a.const_func() < b.const_func();
    }, {"self", "other"});
  h.add_overload_set(hello_lt);

  ligo::overload_set hello_func("func");
  hello_func.add_overload(&hello::func, {"self"});
  h.add_overload_set(hello_func);

  ligo::overload_set hello_const_func("const_func");
  hello_const_func.add_overload(&hello::const_func, {"self"});
  h.add_overload_set(hello_const_func);

  ligo::overload_set hello_const_noexcept_func("const_noexcept_func");
  hello_const_noexcept_func.add_overload(&hello::const_noexcept_func, {"self"});
  h.add_overload_set(hello_const_noexcept_func);

  mod.add_type(h);

  ligo::python_type<world> w("world", "world test class");
  ligo::overload_set world_init("__init__");
  world_init.add_overload([](world& self) {
      new (&self) world{};
    }, {"self"});
  world_init.add_implicit_overload([](world& self, const hello& h) {
      new (&self) world{h};
    }, {"self", "hello"});
  w.add_overload_set(world_init);

  ligo::overload_set world_test_return_hello("test_return_hello");
  world_test_return_hello.add_overload(&world::test_return_hello, {"a"});
  w.add_overload_set(world_test_return_hello);

  mod.add_type(w);

  ligo::overload_set tbo("type_based_overloading");
  tbo.add_overload([](const hello& h) -> PyObject* { Py_RETURN_TRUE; }, {"a"});
  tbo.add_overload([](const world& h) -> PyObject* {
      Py_RETURN_FALSE; }, {"a"});
  tbo.add_overload([](PyObject* a) -> PyObject* {
      Py_INCREF(a);
      return a;
  }, {"a"});
  mod.add_overload_set(tbo);

  ligo::overload_set tboc("type_based_overload_casting");
  tboc.add_overload([](const world& h) -> PyObject* { Py_RETURN_TRUE; }, {"a"});
  mod.add_overload_set(tboc);

  return mod.init();
}
