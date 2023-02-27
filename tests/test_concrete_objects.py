import pytest

import test_concrete_objects_ext

import numpy as np
import array

class hello:
    pass

def test_none_arg():
    assert not test_concrete_objects_ext.none_arg(1)
    assert test_concrete_objects_ext.none_arg(None)
    assert not test_concrete_objects_ext.none_arg(False)
    assert not test_concrete_objects_ext.none_arg(hello)
    assert not test_concrete_objects_ext.none_arg(hello())
    assert not test_concrete_objects_ext.none_arg(lambda x: True)


def test_bool_arg():
    assert not test_concrete_objects_ext.bool_arg(1)
    assert not test_concrete_objects_ext.bool_arg(None)
    assert test_concrete_objects_ext.bool_arg(False)
    assert test_concrete_objects_ext.bool_arg(True)
    assert not test_concrete_objects_ext.bool_arg(hello)
    assert not test_concrete_objects_ext.bool_arg(hello())
    assert not test_concrete_objects_ext.bool_arg(lambda x: True)


def test_long_arg():
    assert test_concrete_objects_ext.long_arg(1)
    assert not test_concrete_objects_ext.long_arg(1.1)
    assert not test_concrete_objects_ext.long_arg(np.double(1.0))
    assert not test_concrete_objects_ext.long_arg(np.uint64(10))
    assert not test_concrete_objects_ext.long_arg(None)
    assert test_concrete_objects_ext.long_arg(False)
    assert test_concrete_objects_ext.long_arg(True)
    assert not test_concrete_objects_ext.long_arg(hello)
    assert not test_concrete_objects_ext.long_arg(hello())
    assert not test_concrete_objects_ext.long_arg(lambda x: True)


def test_float_arg():
    assert not test_concrete_objects_ext.float_arg(1)
    assert test_concrete_objects_ext.float_arg(1.0)
    assert test_concrete_objects_ext.float_arg(1.1)
    assert test_concrete_objects_ext.float_arg(np.double(1.0))
    assert not test_concrete_objects_ext.float_arg(np.uint64(10))
    assert not test_concrete_objects_ext.float_arg(None)
    assert not test_concrete_objects_ext.float_arg(False)
    assert not test_concrete_objects_ext.float_arg(True)
    assert not test_concrete_objects_ext.float_arg(hello)
    assert not test_concrete_objects_ext.float_arg(hello())
    assert not test_concrete_objects_ext.float_arg(lambda x: True)

def test_complex_arg():
    assert test_concrete_objects_ext.complex_arg(complex(1, 1))
    assert not test_concrete_objects_ext.complex_arg(1)
    assert not test_concrete_objects_ext.complex_arg(1.0)
    assert not test_concrete_objects_ext.complex_arg(1.1)
    assert not test_concrete_objects_ext.complex_arg(np.double(1.0))
    assert not test_concrete_objects_ext.complex_arg(np.uint64(10))
    assert not test_concrete_objects_ext.complex_arg(None)
    assert not test_concrete_objects_ext.complex_arg(False)
    assert not test_concrete_objects_ext.complex_arg(True)
    assert not test_concrete_objects_ext.complex_arg(hello)
    assert not test_concrete_objects_ext.complex_arg(hello())
    assert not test_concrete_objects_ext.complex_arg(lambda x: True)


def test_unicode_arg():
    assert test_concrete_objects_ext.unicode_arg("test")
    assert not test_concrete_objects_ext.unicode_arg(1)
    assert not test_concrete_objects_ext.unicode_arg(1.0)
    assert not test_concrete_objects_ext.unicode_arg(1.1)
    assert not test_concrete_objects_ext.unicode_arg(np.double(1.0))
    assert not test_concrete_objects_ext.unicode_arg(np.uint64(10))
    assert not test_concrete_objects_ext.unicode_arg(None)
    assert not test_concrete_objects_ext.unicode_arg(False)
    assert not test_concrete_objects_ext.unicode_arg(True)
    assert not test_concrete_objects_ext.unicode_arg(hello)
    assert not test_concrete_objects_ext.unicode_arg(hello())
    assert not test_concrete_objects_ext.unicode_arg(lambda x: True)

def test_tuple_arg():
    assert test_concrete_objects_ext.tuple_arg((1, 2))
    assert test_concrete_objects_ext.tuple_arg((1,))
    assert not test_concrete_objects_ext.tuple_arg(1)
    assert not test_concrete_objects_ext.tuple_arg(1.0)
    assert not test_concrete_objects_ext.tuple_arg(1.1)
    assert not test_concrete_objects_ext.tuple_arg(np.double(1.0))
    assert not test_concrete_objects_ext.tuple_arg(np.uint64(10))
    assert not test_concrete_objects_ext.tuple_arg(None)
    assert not test_concrete_objects_ext.tuple_arg(False)
    assert not test_concrete_objects_ext.tuple_arg(True)
    assert not test_concrete_objects_ext.tuple_arg(hello)
    assert not test_concrete_objects_ext.tuple_arg(hello())
    assert not test_concrete_objects_ext.tuple_arg(lambda x: True)

def test_list_arg():
    assert test_concrete_objects_ext.list_arg([1, 2])
    assert not test_concrete_objects_ext.list_arg((1, 2))
    assert not test_concrete_objects_ext.list_arg(1)
    assert not test_concrete_objects_ext.list_arg(1.0)
    assert not test_concrete_objects_ext.list_arg(1.1)
    assert not test_concrete_objects_ext.list_arg(np.double(1.0))
    assert not test_concrete_objects_ext.list_arg(np.uint64(10))
    assert not test_concrete_objects_ext.list_arg(None)
    assert not test_concrete_objects_ext.list_arg(False)
    assert not test_concrete_objects_ext.list_arg(True)
    assert not test_concrete_objects_ext.list_arg(hello)
    assert not test_concrete_objects_ext.list_arg(hello())
    assert not test_concrete_objects_ext.list_arg(lambda x: True)

def test_dictionary_arg():
    assert test_concrete_objects_ext.dictionary_arg({"a": 1, "b": 2})
    assert not test_concrete_objects_ext.dictionary_arg(1)
    assert not test_concrete_objects_ext.dictionary_arg(1.0)
    assert not test_concrete_objects_ext.dictionary_arg(1.1)
    assert not test_concrete_objects_ext.dictionary_arg(np.double(1.0))
    assert not test_concrete_objects_ext.dictionary_arg(np.uint64(10))
    assert not test_concrete_objects_ext.dictionary_arg(None)
    assert not test_concrete_objects_ext.dictionary_arg(False)
    assert not test_concrete_objects_ext.dictionary_arg(True)
    assert not test_concrete_objects_ext.dictionary_arg(hello)
    assert not test_concrete_objects_ext.dictionary_arg(hello())
    assert not test_concrete_objects_ext.dictionary_arg(lambda x: True)

def test_set_arg():
    assert test_concrete_objects_ext.set_arg({"a", "b"})
    assert not test_concrete_objects_ext.set_arg(1)
    assert not test_concrete_objects_ext.set_arg(1.0)
    assert not test_concrete_objects_ext.set_arg(1.1)
    assert not test_concrete_objects_ext.set_arg(np.double(1.0))
    assert not test_concrete_objects_ext.set_arg(np.uint64(10))
    assert not test_concrete_objects_ext.set_arg(None)
    assert not test_concrete_objects_ext.set_arg(False)
    assert not test_concrete_objects_ext.set_arg(True)
    assert not test_concrete_objects_ext.set_arg(hello)
    assert not test_concrete_objects_ext.set_arg(hello())
    assert not test_concrete_objects_ext.set_arg(lambda x: True)
