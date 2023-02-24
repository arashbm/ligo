import pytest

import libtest_abstract_objects

import numpy as np
import array

class hello:
    pass

class hello_callable:
    def __call__(self):
        return 1

def test_object_arg():
    assert libtest_abstract_objects.object_arg(1)
    assert libtest_abstract_objects.object_arg(None)
    assert libtest_abstract_objects.object_arg(False)
    assert libtest_abstract_objects.object_arg(hello)
    assert libtest_abstract_objects.object_arg(hello())
    assert libtest_abstract_objects.object_arg(lambda x: True)


def test_callable_arg():
    assert not libtest_abstract_objects.callable_arg(1)
    assert not libtest_abstract_objects.callable_arg(None)
    assert not libtest_abstract_objects.callable_arg(False)
    assert libtest_abstract_objects.callable_arg(hello)
    assert not libtest_abstract_objects.callable_arg(hello())
    assert libtest_abstract_objects.callable_arg(hello_callable)
    assert libtest_abstract_objects.callable_arg(hello_callable)
    assert libtest_abstract_objects.callable_arg(lambda x: True)


def test_number_arg():
    assert libtest_abstract_objects.number_arg(1)
    assert libtest_abstract_objects.number_arg(1.1)
    assert libtest_abstract_objects.number_arg(np.double(1.0))
    assert libtest_abstract_objects.number_arg(np.uint64(10))
    assert not libtest_abstract_objects.number_arg(None)
    assert libtest_abstract_objects.number_arg(False)
    assert libtest_abstract_objects.number_arg(True)
    assert not libtest_abstract_objects.number_arg(hello)
    assert not libtest_abstract_objects.number_arg(hello())
    assert not libtest_abstract_objects.number_arg(lambda x: True)


def test_index_arg():
    assert libtest_abstract_objects.index_arg(1)
    assert not libtest_abstract_objects.index_arg(1.0)
    assert not libtest_abstract_objects.index_arg(1.1)
    assert not libtest_abstract_objects.index_arg(np.double(1.0))
    assert libtest_abstract_objects.index_arg(np.uint64(10))
    assert not libtest_abstract_objects.index_arg(None)
    assert libtest_abstract_objects.index_arg(False)
    assert libtest_abstract_objects.index_arg(True)
    assert not libtest_abstract_objects.index_arg(hello)
    assert not libtest_abstract_objects.index_arg(hello())
    assert not libtest_abstract_objects.index_arg(lambda x: True)


def test_sequence_arg():
    assert not libtest_abstract_objects.sequence_arg(1)
    assert not libtest_abstract_objects.sequence_arg(np.double(1.0))
    assert not libtest_abstract_objects.sequence_arg(np.uint64(10))
    assert not libtest_abstract_objects.sequence_arg(None)
    assert not libtest_abstract_objects.sequence_arg(False)
    assert not libtest_abstract_objects.sequence_arg(True)
    assert not libtest_abstract_objects.sequence_arg(hello)
    assert not libtest_abstract_objects.sequence_arg(hello())
    assert not libtest_abstract_objects.sequence_arg(lambda x: True)
    assert libtest_abstract_objects.sequence_arg([1, 2, 3, 4, 5])
    assert libtest_abstract_objects.sequence_arg(array.array('d', [1.0, 3.14]))
    assert libtest_abstract_objects.sequence_arg(np.array([1.0, 3.14]))
    assert not libtest_abstract_objects.sequence_arg({'a': 1, 'b': 2})  # Maybe?

@pytest.mark.xfail
def test_mapping_arg_numpy_scalars():
    # numpy scalars for some reason return true for PyMapping_Check.
    assert not libtest_abstract_objects.mapping_arg(np.double(1.0))
    assert not libtest_abstract_objects.mapping_arg(np.uint64(10))

def test_mapping_arg():
    assert not libtest_abstract_objects.mapping_arg(1)
    assert not libtest_abstract_objects.mapping_arg(None)
    assert not libtest_abstract_objects.mapping_arg(False)
    assert not libtest_abstract_objects.mapping_arg(True)
    assert not libtest_abstract_objects.mapping_arg(hello)
    assert not libtest_abstract_objects.mapping_arg(hello())
    assert not libtest_abstract_objects.mapping_arg(lambda x: True)
    assert libtest_abstract_objects.mapping_arg([1, 2, 3, 4, 5])
    assert libtest_abstract_objects.mapping_arg(array.array('d', [1.0, 3.14]))
    assert libtest_abstract_objects.mapping_arg(np.array([1.0, 3.14]))
    assert libtest_abstract_objects.mapping_arg({'a': 1, 'b': 2})
