#include <functional>

#include <ligo/ligo.hpp>

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

LIGO_MODULE(test_types_ext, "module for testing types", mod) {
  ligo::python_type<int> int_type("int", "int type");
  int_type.define_method("__repr__", [](int a_param){
                           return PyUnicode_FromFormat("%i", a_param);
                         }, {{"a"}});
  int_type.define_method("__eq__", std::equal_to<int>{}, {{"a"}, {"b"}});
  int_type.define_method("__ne__", std::not_equal_to<int>{}, {{"a"}, {"b"}});
  mod.add_type(int_type);


  ligo::python_type<hello> hlo("hello", "hello test class");
  hlo.define_method("__init__", [](hello& self) {
                      new (&self) hello{};
                    }, {{"self"}});
  hlo.define_method("__lt__", [](const hello& a_param, const hello& another_param) {
                      return a_param.const_func() < another_param.const_func();
                    }, {{"self"}, {"other"}});
  hlo.define_method("func", &hello::func, {{"self"}});
  hlo.define_method("const_func", &hello::const_func, {{"self"}});
  hlo.define_method("const_noexcept_func", &hello::const_noexcept_func, {{"self"}});
  mod.add_type(hlo);


  ligo::python_type<world> wrld("world", "world test class");
  wrld.overload_method("__init__", [](world& self) {
                         new (&self) world{};
                       }, {{"self"}});
  wrld.implicit_overload_method("__init__", [](world& self, const hello& hlo) {
                         new (&self) world{hlo};
                       }, {{"self"}, {"hello"}});
  wrld.define_method("test_return_hello", &world::test_return_hello, {{"a"}});
  mod.add_type(wrld);


  mod.overload_method("type_based_overloading",
                      [](const hello& /* hlo */) -> PyObject* {
                        Py_RETURN_TRUE;
                      }, {{"a"}});
  mod.overload_method("type_based_overloading",
                      [](const world& /* wrld */) -> PyObject* {
                        Py_RETURN_FALSE;
                      }, {{"a"}});
  mod.overload_method("type_based_overloading",
                      [](PyObject* a_param) -> PyObject* {
                        Py_INCREF(a_param);
                        return a_param;
                      }, {{"a"}});

  mod.define_method("type_based_overload_casting",
                    [](const world& /* hlo */) -> PyObject* {
                      Py_RETURN_TRUE;
                    }, {{"a"}});
}
