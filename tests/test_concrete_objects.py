import pytest

import libtest_concrete_objects

import numpy as np
import array

class hello:
    pass

def test_none_arg():
    assert not libtest_concrete_objects.none_arg(1)
    assert libtest_concrete_objects.none_arg(None)
    assert not libtest_concrete_objects.none_arg(False)
    assert not libtest_concrete_objects.none_arg(hello)
    assert not libtest_concrete_objects.none_arg(hello())
    assert not libtest_concrete_objects.none_arg(lambda x: True)


def test_bool_arg():
    assert not libtest_concrete_objects.bool_arg(1)
    assert not libtest_concrete_objects.bool_arg(None)
    assert libtest_concrete_objects.bool_arg(False)
    assert libtest_concrete_objects.bool_arg(True)
    assert not libtest_concrete_objects.bool_arg(hello)
    assert not libtest_concrete_objects.bool_arg(hello())
    assert not libtest_concrete_objects.bool_arg(lambda x: True)


def test_long_arg():
    assert libtest_concrete_objects.long_arg(1)
    assert not libtest_concrete_objects.long_arg(1.1)
    assert not libtest_concrete_objects.long_arg(np.double(1.0))
    assert not libtest_concrete_objects.long_arg(np.uint64(10))
    assert not libtest_concrete_objects.long_arg(None)
    assert libtest_concrete_objects.long_arg(False)
    assert libtest_concrete_objects.long_arg(True)
    assert not libtest_concrete_objects.long_arg(hello)
    assert not libtest_concrete_objects.long_arg(hello())
    assert not libtest_concrete_objects.long_arg(lambda x: True)


def test_float_arg():
    assert not libtest_concrete_objects.float_arg(1)
    assert libtest_concrete_objects.float_arg(1.0)
    assert libtest_concrete_objects.float_arg(1.1)
    assert libtest_concrete_objects.float_arg(np.double(1.0))
    assert not libtest_concrete_objects.float_arg(np.uint64(10))
    assert not libtest_concrete_objects.float_arg(None)
    assert not libtest_concrete_objects.float_arg(False)
    assert not libtest_concrete_objects.float_arg(True)
    assert not libtest_concrete_objects.float_arg(hello)
    assert not libtest_concrete_objects.float_arg(hello())
    assert not libtest_concrete_objects.float_arg(lambda x: True)

def test_complex_arg():
    assert libtest_concrete_objects.complex_arg(complex(1, 1))
    assert not libtest_concrete_objects.complex_arg(1)
    assert not libtest_concrete_objects.complex_arg(1.0)
    assert not libtest_concrete_objects.complex_arg(1.1)
    assert not libtest_concrete_objects.complex_arg(np.double(1.0))
    assert not libtest_concrete_objects.complex_arg(np.uint64(10))
    assert not libtest_concrete_objects.complex_arg(None)
    assert not libtest_concrete_objects.complex_arg(False)
    assert not libtest_concrete_objects.complex_arg(True)
    assert not libtest_concrete_objects.complex_arg(hello)
    assert not libtest_concrete_objects.complex_arg(hello())
    assert not libtest_concrete_objects.complex_arg(lambda x: True)


def test_unicode_arg():
    assert libtest_concrete_objects.unicode_arg("test")
    assert not libtest_concrete_objects.unicode_arg(1)
    assert not libtest_concrete_objects.unicode_arg(1.0)
    assert not libtest_concrete_objects.unicode_arg(1.1)
    assert not libtest_concrete_objects.unicode_arg(np.double(1.0))
    assert not libtest_concrete_objects.unicode_arg(np.uint64(10))
    assert not libtest_concrete_objects.unicode_arg(None)
    assert not libtest_concrete_objects.unicode_arg(False)
    assert not libtest_concrete_objects.unicode_arg(True)
    assert not libtest_concrete_objects.unicode_arg(hello)
    assert not libtest_concrete_objects.unicode_arg(hello())
    assert not libtest_concrete_objects.unicode_arg(lambda x: True)

def test_tuple_arg():
    assert libtest_concrete_objects.tuple_arg((1, 2))
    assert libtest_concrete_objects.tuple_arg((1,))
    assert not libtest_concrete_objects.tuple_arg(1)
    assert not libtest_concrete_objects.tuple_arg(1.0)
    assert not libtest_concrete_objects.tuple_arg(1.1)
    assert not libtest_concrete_objects.tuple_arg(np.double(1.0))
    assert not libtest_concrete_objects.tuple_arg(np.uint64(10))
    assert not libtest_concrete_objects.tuple_arg(None)
    assert not libtest_concrete_objects.tuple_arg(False)
    assert not libtest_concrete_objects.tuple_arg(True)
    assert not libtest_concrete_objects.tuple_arg(hello)
    assert not libtest_concrete_objects.tuple_arg(hello())
    assert not libtest_concrete_objects.tuple_arg(lambda x: True)

def test_list_arg():
    assert libtest_concrete_objects.list_arg([1, 2])
    assert not libtest_concrete_objects.list_arg((1, 2))
    assert not libtest_concrete_objects.list_arg(1)
    assert not libtest_concrete_objects.list_arg(1.0)
    assert not libtest_concrete_objects.list_arg(1.1)
    assert not libtest_concrete_objects.list_arg(np.double(1.0))
    assert not libtest_concrete_objects.list_arg(np.uint64(10))
    assert not libtest_concrete_objects.list_arg(None)
    assert not libtest_concrete_objects.list_arg(False)
    assert not libtest_concrete_objects.list_arg(True)
    assert not libtest_concrete_objects.list_arg(hello)
    assert not libtest_concrete_objects.list_arg(hello())
    assert not libtest_concrete_objects.list_arg(lambda x: True)

def test_dictionary_arg():
    assert libtest_concrete_objects.dictionary_arg({"a": 1, "b": 2})
    assert not libtest_concrete_objects.dictionary_arg(1)
    assert not libtest_concrete_objects.dictionary_arg(1.0)
    assert not libtest_concrete_objects.dictionary_arg(1.1)
    assert not libtest_concrete_objects.dictionary_arg(np.double(1.0))
    assert not libtest_concrete_objects.dictionary_arg(np.uint64(10))
    assert not libtest_concrete_objects.dictionary_arg(None)
    assert not libtest_concrete_objects.dictionary_arg(False)
    assert not libtest_concrete_objects.dictionary_arg(True)
    assert not libtest_concrete_objects.dictionary_arg(hello)
    assert not libtest_concrete_objects.dictionary_arg(hello())
    assert not libtest_concrete_objects.dictionary_arg(lambda x: True)

def test_set_arg():
    assert libtest_concrete_objects.set_arg({"a", "b"})
    assert not libtest_concrete_objects.set_arg(1)
    assert not libtest_concrete_objects.set_arg(1.0)
    assert not libtest_concrete_objects.set_arg(1.1)
    assert not libtest_concrete_objects.set_arg(np.double(1.0))
    assert not libtest_concrete_objects.set_arg(np.uint64(10))
    assert not libtest_concrete_objects.set_arg(None)
    assert not libtest_concrete_objects.set_arg(False)
    assert not libtest_concrete_objects.set_arg(True)
    assert not libtest_concrete_objects.set_arg(hello)
    assert not libtest_concrete_objects.set_arg(hello())
    assert not libtest_concrete_objects.set_arg(lambda x: True)
