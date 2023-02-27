import pytest

import test_types_ext


def test_types():
    assert test_types_ext.hello()
    assert test_types_ext.world()


def test_type_bound_methods():
    h = test_types_ext.hello()
    const_func_method = h.const_func
    assert h.const_func() == const_func_method()


def test_type_unbound_methods():
    h = test_types_ext.hello()
    const_func_method = test_types_ext.hello.const_func
    assert h.const_func() == const_func_method(h)


def test_type_method_return_type_mappings():
    w = test_types_ext.world()
    assert isinstance(w.test_return_hello(), test_types_ext.hello)
    assert isinstance(
            test_types_ext.world.test_return_hello(w), test_types_ext.hello)


def test_type_method_argument_type_mappings():
    h = test_types_ext.hello()
    assert isinstance(test_types_ext.world(h), test_types_ext.world)


def test_type_operators():
    h1 = test_types_ext.hello()
    h2 = test_types_ext.hello()
    assert not h1 < h2
    with pytest.raises(TypeError) as excinfo:
        h1 < 12
    assert "'<' not supported between instances of" in str(excinfo)


def test_type_method_mutation():
    h1 = test_types_ext.hello()
    h2 = test_types_ext.hello()
    assert h1.const_func() == h2.const_func()
    h1.func()
    assert h1.const_func() != h2.const_func()
    h2.func()
    assert h1.const_func() == h2.const_func()


def test_type_overloads():
    h = test_types_ext.hello()
    assert test_types_ext.type_based_overloading(h) is True

    w = test_types_ext.world()
    assert test_types_ext.type_based_overloading(w) is False

    assert 12 == test_types_ext.type_based_overloading(12)


def test_type_overload_casting():
    w = test_types_ext.world()
    assert test_types_ext.type_based_overload_casting(w)

    h = test_types_ext.hello()
    assert test_types_ext.type_based_overload_casting(h)
