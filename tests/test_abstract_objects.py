import pytest

import test_abstract_objects_ext

import numpy as np
import array

class hello:
    pass

class hello_callable:
    def __call__(self):
        return 1

def test_object_arg():
    assert test_abstract_objects_ext.object_arg(1)
    assert test_abstract_objects_ext.object_arg(None)
    assert test_abstract_objects_ext.object_arg(False)
    assert test_abstract_objects_ext.object_arg(hello)
    assert test_abstract_objects_ext.object_arg(hello())
    assert test_abstract_objects_ext.object_arg(lambda x: True)


def test_callable_arg():
    assert not test_abstract_objects_ext.callable_arg(1)
    assert not test_abstract_objects_ext.callable_arg(None)
    assert not test_abstract_objects_ext.callable_arg(False)
    assert test_abstract_objects_ext.callable_arg(hello)
    assert not test_abstract_objects_ext.callable_arg(hello())
    assert test_abstract_objects_ext.callable_arg(hello_callable)
    assert test_abstract_objects_ext.callable_arg(hello_callable)
    assert test_abstract_objects_ext.callable_arg(lambda x: True)


def test_number_arg():
    assert test_abstract_objects_ext.number_arg(1)
    assert test_abstract_objects_ext.number_arg(1.1)
    assert test_abstract_objects_ext.number_arg(np.double(1.0))
    assert test_abstract_objects_ext.number_arg(np.uint64(10))
    assert not test_abstract_objects_ext.number_arg(None)
    assert test_abstract_objects_ext.number_arg(False)
    assert test_abstract_objects_ext.number_arg(True)
    assert not test_abstract_objects_ext.number_arg(hello)
    assert not test_abstract_objects_ext.number_arg(hello())
    assert not test_abstract_objects_ext.number_arg(lambda x: True)


def test_index_arg():
    assert test_abstract_objects_ext.index_arg(1)
    assert not test_abstract_objects_ext.index_arg(1.0)
    assert not test_abstract_objects_ext.index_arg(1.1)
    assert not test_abstract_objects_ext.index_arg(np.double(1.0))
    assert test_abstract_objects_ext.index_arg(np.uint64(10))
    assert not test_abstract_objects_ext.index_arg(None)
    assert test_abstract_objects_ext.index_arg(False)
    assert test_abstract_objects_ext.index_arg(True)
    assert not test_abstract_objects_ext.index_arg(hello)
    assert not test_abstract_objects_ext.index_arg(hello())
    assert not test_abstract_objects_ext.index_arg(lambda x: True)


def test_sequence_arg():
    assert not test_abstract_objects_ext.sequence_arg(1)
    assert not test_abstract_objects_ext.sequence_arg(np.double(1.0))
    assert not test_abstract_objects_ext.sequence_arg(np.uint64(10))
    assert not test_abstract_objects_ext.sequence_arg(None)
    assert not test_abstract_objects_ext.sequence_arg(False)
    assert not test_abstract_objects_ext.sequence_arg(True)
    assert not test_abstract_objects_ext.sequence_arg(hello)
    assert not test_abstract_objects_ext.sequence_arg(hello())
    assert not test_abstract_objects_ext.sequence_arg(lambda x: True)
    assert test_abstract_objects_ext.sequence_arg([1, 2, 3, 4, 5])
    assert test_abstract_objects_ext.sequence_arg(array.array('d', [1.0, 3.14]))
    assert test_abstract_objects_ext.sequence_arg(np.array([1.0, 3.14]))
    assert not test_abstract_objects_ext.sequence_arg({'a': 1, 'b': 2})  # Maybe?

@pytest.mark.xfail
def test_mapping_arg_numpy_scalars():
    # numpy scalars for some reason return true for PyMapping_Check.
    assert not test_abstract_objects_ext.mapping_arg(np.double(1.0))
    assert not test_abstract_objects_ext.mapping_arg(np.uint64(10))

def test_mapping_arg():
    assert not test_abstract_objects_ext.mapping_arg(1)
    assert not test_abstract_objects_ext.mapping_arg(None)
    assert not test_abstract_objects_ext.mapping_arg(False)
    assert not test_abstract_objects_ext.mapping_arg(True)
    assert not test_abstract_objects_ext.mapping_arg(hello)
    assert not test_abstract_objects_ext.mapping_arg(hello())
    assert not test_abstract_objects_ext.mapping_arg(lambda x: True)
    assert test_abstract_objects_ext.mapping_arg([1, 2, 3, 4, 5])
    assert test_abstract_objects_ext.mapping_arg(array.array('d', [1.0, 3.14]))
    assert test_abstract_objects_ext.mapping_arg(np.array([1.0, 3.14]))
    assert test_abstract_objects_ext.mapping_arg({'a': 1, 'b': 2})
