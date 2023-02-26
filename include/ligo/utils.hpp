#ifndef INCLUDE_LIGO_UTILS_HPP_
#define INCLUDE_LIGO_UTILS_HPP_

#include "metal.hpp"

namespace ligo {
  template <typename... Args>
  struct resolve_t {
      template <typename R, bool X>
      constexpr auto operator()(R(*func)(Args...) noexcept(X)) const noexcept
            -> decltype(func) {
          return func;
      }

      template <typename R, class C, bool X>
      constexpr auto
      operator()(R(C::*member_func)(Args...) noexcept(X)) const noexcept
            -> decltype(member_func) {
          return member_func;
      }
  };

  template <typename... Args>
  static constexpr resolve_t<Args...> resolve{};

  template<typename F>
  struct function_traits {
      using op_traits = function_traits<decltype(&F::operator())>;

      using result_type = typename op_traits::result_type;
      using args = metal::drop<typename op_traits::args, metal::number<1>>;
      static constexpr std::size_t arity = op_traits::arity - 1;
      static constexpr bool no_except = op_traits::no_except;
  };

  template<typename R, bool X, typename ...Args>
  struct function_traits<R(Args...) noexcept(X)> {
      static constexpr std::size_t arity = sizeof...(Args);
      using result_type = R;
      using args = metal::list<Args...>;
      static constexpr bool no_except = X;
  };

  template<typename R, bool X, typename ...Args>
  struct function_traits<R(*)(Args...) noexcept(X)>
    : public function_traits<R(Args...) noexcept(X)> {};

  template<typename C, typename R, bool X, typename ...Args>
  struct function_traits<R(C::*)(Args...) noexcept(X)>
    : public function_traits<R(C&, Args...) noexcept(X)> {};

  template<typename C, typename R, bool X, typename ...Args>
  struct function_traits<R(C::*)(Args...) const noexcept(X)>
    : public function_traits<R(C&, Args...) noexcept(X)> {};
}  // namespace ligo

#endif  // INCLUDE_LIGO_UTILS_HPP_
