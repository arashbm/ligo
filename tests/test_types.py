import pytest

import libtest_types


def test_types():
    assert libtest_types.hello()
    assert libtest_types.world()


def test_type_bound_methods():
    h = libtest_types.hello()
    const_func_method = h.const_func
    assert h.const_func() == const_func_method()


def test_type_unbound_methods():
    h = libtest_types.hello()
    const_func_method = libtest_types.hello.const_func
    assert h.const_func() == const_func_method(h)


def test_type_method_return_type_mappings():
    w = libtest_types.world()
    assert isinstance(w.test_return_hello(), libtest_types.hello)
    assert isinstance(
            libtest_types.world.test_return_hello(w), libtest_types.hello)


def test_type_method_argument_type_mappings():
    h = libtest_types.hello()
    assert isinstance(libtest_types.world(h), libtest_types.world)


def test_type_operators():
    h1 = libtest_types.hello()
    h2 = libtest_types.hello()
    assert not h1 < h2
    with pytest.raises(TypeError) as excinfo:
        h1 < 12
    assert "'<' not supported between instances of" in str(excinfo)


def test_type_method_mutation():
    h1 = libtest_types.hello()
    h2 = libtest_types.hello()
    assert h1.const_func() == h2.const_func()
    h1.func()
    assert h1.const_func() != h2.const_func()
    h2.func()
    assert h1.const_func() == h2.const_func()


def test_type_overloads():
    h = libtest_types.hello()
    assert libtest_types.type_based_overloading(h) is True

    w = libtest_types.world()
    assert libtest_types.type_based_overloading(w) is False

    assert 12 == libtest_types.type_based_overloading(12)


def test_type_overload_casting():
    w = libtest_types.world()
    assert libtest_types.type_based_overload_casting(w)

    h = libtest_types.hello()
    assert libtest_types.type_based_overload_casting(h)
