import pytest

import test_exceptions_ext

def method_throws(method, exception, message=None):
    def test_func():
        with pytest.raises(exception) as excinfo:
            method()
        if message:
            assert message in str(excinfo)
    return test_func

test_python_exception = method_throws(
        test_exceptions_ext.test_python_exception,
        RuntimeError, "threw python_exception")

test_throw_object = method_throws(
        test_exceptions_ext.test_throw_object,
        RuntimeError)

test_bad_alloc = method_throws(
        test_exceptions_ext.test_bad_alloc,
        MemoryError)

test_domain_error = method_throws(
        test_exceptions_ext.test_domain_error,
        ValueError, "threw domain_error")

test_invalid_argument = method_throws(
        test_exceptions_ext.test_invalid_argument,
        ValueError, "threw invalid_argument")

test_length_error = method_throws(
        test_exceptions_ext.test_length_error,
        ValueError, "threw length_error")

test_out_of_range = method_throws(
        test_exceptions_ext.test_out_of_range,
        IndexError, "threw out_of_range")

test_range_error = method_throws(
        test_exceptions_ext.test_range_error,
        ValueError, "threw range_error")

test_overflow_error = method_throws(
        test_exceptions_ext.test_overflow_error,
        OverflowError, "threw overflow_error")

test_exception = method_throws(
        test_exceptions_ext.test_exception,
        RuntimeError)

test_exception_subclass = method_throws(
        test_exceptions_ext.test_exception_subclass,
        RuntimeError, "threw hello_exception")
