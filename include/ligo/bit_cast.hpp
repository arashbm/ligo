#ifndef INCLUDE_LIGO_BIT_CAST_HPP_
#define INCLUDE_LIGO_BIT_CAST_HPP_

#include <type_traits>
#include <cstring>

namespace ligo {
  template <typename T>
  concept trivially_copyable = std::is_trivially_copyable_v<T>;

  // bit_cast shim for the unfortunate Apple Clang
  template <trivially_copyable To, trivially_copyable From>
  requires (sizeof(To) == sizeof(From))
  To bit_cast(const From& src) noexcept {
    To dst{};
    std::memcpy(static_cast<void*>(&dst), &src,
                sizeof(dst));  // NOLINT(bugprone-sizeof-expression)
    return dst;
  }
}  // namespace ligo

#endif  // INCLUDE_LIGO_BIT_CAST_HPP_
