import test_methods_ext

def test_overload():
    assert test_methods_ext.simple_overloading()
    assert 12 == test_methods_ext.simple_overloading(12)

def test_no_capturing_lambda():
    assert test_methods_ext.no_capture_lambda()

def test_noexcept_lambda():
    assert test_methods_ext.noexcept_lambda()

def test_capturing_lambda():
    assert test_methods_ext.capturing_lambda() == 12 + 43 + 22 - 1

def test_function_pointer():
    assert test_methods_ext.fpointer(12, 12)
    assert test_methods_ext.fpointer_noexcept(12, 12)
