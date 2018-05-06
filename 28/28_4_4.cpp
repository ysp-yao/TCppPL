#include <type_traits>

struct subsitution_failure {};

template<typename T>
struct substitution_secceeded : std::true_type
{};

template<>
struct substitution_secceeded<subsitution_failure> : std::false_type
{};

template<typename T>
struct get_f_result {
private:
  template<typename X>
    static auto check(X const& x) -> decltype(f(x));
  static subsitution_failure check(...);
public:
  using type = decltype(check(std::declval<T>()));
};

template<typename T>
struct has_f
  :substitution_secceeded<typename get_f_result<T>::type>
{};

template<typename T>
constexpr bool Has_f()
{
  return has_f<T>::value;
}

template<typename T>
class X {
  Enable_if<Has_f<T>()> use_f(const T&)
  {
    f(t);
  }
};