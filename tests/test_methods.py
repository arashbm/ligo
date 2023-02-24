import libtest_methods

def test_overload():
    assert libtest_methods.simple_overloading()
    assert 12 == libtest_methods.simple_overloading(12)

def test_no_capturing_lambda():
    assert libtest_methods.no_capture_lambda()

def test_noexcept_lambda():
    assert libtest_methods.noexcept_lambda()

def test_capturing_lambda():
    assert libtest_methods.capturing_lambda() == 12 + 43 + 22 - 1

def test_function_pointer():
    assert libtest_methods.fpointer(12, 12)
    assert libtest_methods.fpointer_noexcept(12, 12)
