#ifndef INCLUDE_LIGO_GIL_HPP_
#define INCLUDE_LIGO_GIL_HPP_

#include "python.hpp"

#include <utility>
#include <functional>

#include "metal.hpp"

namespace ligo {
  class gil_scoped_acquire {
  public:
    gil_scoped_acquire() noexcept : _lock_state{PyGILState_Ensure()} {}
    gil_scoped_acquire(gil_scoped_acquire&) = delete;
    gil_scoped_acquire(gil_scoped_acquire&&) = default;
    gil_scoped_acquire& operator=(const gil_scoped_acquire&) = delete;
    gil_scoped_acquire& operator=(gil_scoped_acquire&&) = default;
    ~gil_scoped_acquire() { PyGILState_Release(_lock_state); }
  private:
    PyGILState_STATE _lock_state;
  };

  class gil_scoped_release {
  public:
    gil_scoped_release() noexcept : _thread_state{PyEval_SaveThread()} {}
    gil_scoped_release(gil_scoped_release&) = delete;
    gil_scoped_release(gil_scoped_release&&) = default;
    gil_scoped_release& operator=(const gil_scoped_release&) = delete;
    gil_scoped_release& operator=(gil_scoped_release&&) = default;
    ~gil_scoped_release() { PyEval_RestoreThread(_thread_state); }
  private:
    PyThreadState* _thread_state;
  };

  template <typename ...Guards>
  class call_gurad {
    using guards = metal::list<Guards...>;
  };
}  // namespace ligo

#endif  // INCLUDE_LIGO_ABSTRACT_OBJECTS_HPP_
