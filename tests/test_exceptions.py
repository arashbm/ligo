import pytest

import libtest_exceptions

def method_throws(method, exception, message=None):
    def test_func():
        with pytest.raises(exception) as excinfo:
            method()
        if message:
            assert message in str(excinfo)
    return test_func

test_python_exception = method_throws(
        libtest_exceptions.test_python_exception,
        RuntimeError, "threw python_exception")

test_throw_object = method_throws(
        libtest_exceptions.test_throw_object,
        RuntimeError)

test_bad_alloc = method_throws(
        libtest_exceptions.test_bad_alloc,
        MemoryError)

test_domain_error = method_throws(
        libtest_exceptions.test_domain_error,
        ValueError, "threw domain_error")

test_invalid_argument = method_throws(
        libtest_exceptions.test_invalid_argument,
        ValueError, "threw invalid_argument")

test_length_error = method_throws(
        libtest_exceptions.test_length_error,
        ValueError, "threw length_error")

test_out_of_range = method_throws(
        libtest_exceptions.test_out_of_range,
        IndexError, "threw out_of_range")

test_range_error = method_throws(
        libtest_exceptions.test_range_error,
        ValueError, "threw range_error")

test_overflow_error = method_throws(
        libtest_exceptions.test_overflow_error,
        OverflowError, "threw overflow_error")

test_exception = method_throws(
        libtest_exceptions.test_exception,
        RuntimeError)

test_exception_subclass = method_throws(
        libtest_exceptions.test_exception_subclass,
        RuntimeError, "threw hello_exception")
