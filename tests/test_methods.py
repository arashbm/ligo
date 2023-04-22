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


def test_default_arg():
    assert not test_methods_ext.default_arg(False)
    assert test_methods_ext.default_arg(True)
    assert test_methods_ext.default_arg()


def test_mixing_mandatory_and_default_arg():
    assert not test_methods_ext.some_default_arg(False, False)
    assert test_methods_ext.some_default_arg(False, True)
    assert test_methods_ext.some_default_arg(False)


def test_gil_default():
    assert test_methods_ext.gil_default()


def test_with_no_gil():
    assert not test_methods_ext.with_no_gil()


def test_with_no_gil_params():
    assert not test_methods_ext.with_no_gil_params("blaah")


def test_release_gil():
    assert not test_methods_ext.release_gil()


def test_acquire_gil():
    assert test_methods_ext.acquire_gil()
