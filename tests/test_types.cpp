#include <functional>

#include <ligo/ligo.hpp>

static ligo::python_module mod("libtest_types", "module for testing types");

class hello {
public:
  hello() = default;
  explicit hello(int value) : _value{value} {}

  int func() {
    return _value++;
  }

  [[nodiscard]] int const_func() const {
    return _value;
  }

  [[nodiscard]] int const_noexcept_func() const noexcept {
    return _value;
  }
private:
  int _value;
};

class world {
public:
  world() = default;
  explicit world(const hello& /* hll */) {}
  hello test_return_hello() {
    return hello(1);
  };
};

PyMODINIT_FUNC PyInit_libtest_types() {
  ligo::python_type<int> int_type("int", "int type");
  ligo::overload_set int_repr("__repr__");
  int_repr.add_overload([](int a_param){
      return PyUnicode_FromFormat("%i", a_param);
    }, {"a"});
  int_type.add_overload_set(int_repr);

  ligo::overload_set int_eq("__eq__");
  int_eq.add_overload(std::equal_to<int>{}, {"a", "b"});
  int_type.add_overload_set(int_eq);

  ligo::overload_set int_ne("__ne__");
  int_ne.add_overload(std::not_equal_to<int>{}, {"a", "b"});
  int_type.add_overload_set(int_ne);
  mod.add_type(int_type);

  ligo::python_type<hello> hlo("hello", "hello test class");
  ligo::overload_set hello_init("__init__");
  hello_init.add_overload([](hello& self) {
      new (&self) hello{};
    }, {"self"});
  hlo.add_overload_set(hello_init);

  ligo::overload_set hello_lt("__lt__");
  hello_lt.add_overload([](const hello& a_param, const hello& another_param) {
      return a_param.const_func() < another_param.const_func();
    }, {"self", "other"});
  hlo.add_overload_set(hello_lt);

  ligo::overload_set hello_func("func");
  hello_func.add_overload(&hello::func, {"self"});
  hlo.add_overload_set(hello_func);

  ligo::overload_set hello_const_func("const_func");
  hello_const_func.add_overload(&hello::const_func, {"self"});
  hlo.add_overload_set(hello_const_func);

  ligo::overload_set hello_const_noexcept_func("const_noexcept_func");
  hello_const_noexcept_func.add_overload(&hello::const_noexcept_func, {"self"});
  hlo.add_overload_set(hello_const_noexcept_func);

  mod.add_type(hlo);

  ligo::python_type<world> wrld("world", "world test class");
  ligo::overload_set world_init("__init__");
  world_init.add_overload([](world& self) {
      new (&self) world{};
    }, {"self"});
  world_init.add_implicit_overload([](world& self, const hello& hlo) {
      new (&self) world{hlo};
    }, {"self", "hello"});
  wrld.add_overload_set(world_init);

  ligo::overload_set world_test_return_hello("test_return_hello");
  world_test_return_hello.add_overload(&world::test_return_hello, {"a"});
  wrld.add_overload_set(world_test_return_hello);

  mod.add_type(wrld);

  ligo::overload_set tbo("type_based_overloading");
  tbo.add_overload([](const hello& /* hlo */) -> PyObject* { Py_RETURN_TRUE; }, {"a"});
  tbo.add_overload([](const world& /* wrld */) -> PyObject* {
      Py_RETURN_FALSE; }, {"a"});
  tbo.add_overload([](PyObject* a_param) -> PyObject* {
      Py_INCREF(a_param);
      return a_param;
  }, {"a"});
  mod.add_overload_set(tbo);

  ligo::overload_set tboc("type_based_overload_casting");
  tboc.add_overload([](const world& /* hlo */) -> PyObject* { Py_RETURN_TRUE; }, {"a"});
  mod.add_overload_set(tboc);

  return mod.init();
}
