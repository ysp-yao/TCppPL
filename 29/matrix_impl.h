#include <type_traits>
#include <vector>
#include <array>
#include <cstddef>
#include <iostream>
#include <cassert>

template<bool B, typename T>
using Enable_if = typename std::enable_if<B, T>::type;

template< class From, class To >
using Convertible = typename std::is_convertible<From, To>::value;

namespace Matrix_impl {

  template<typename T, size_t N>
  struct Matrix_init {
    using type = std::initializer_list<typename Matrix_init<T, N - 1>::type>;
  };

  template<typename T>
  struct Matrix_init<T, 1> {
    using type = std::initializer_list<T>;
  };

  template<typename T>
  struct Matrix_init<T, 0>;

  //template<size_t N, typename... Dims>
  //bool check_bounds(const Matrix_slice<N>& slice, Dims... dims)
  //{
  //  size_t indexes[N]{ size_t(dims)... };
  //  return equal(indexes, indexes + N, slice.extents, less<size_t>{});
  //}

  template<typename... Args>
  constexpr bool Requesting_element();

  //constexpr bool All() { return true; }

  //template<typename... Args>
  //constexpr bool All(bool b, Args...args)
  //{
  //  return b && All(args...);
  //}

  //template<typename... Args>
  //constexpr bool Requesting_slice()
  //{
  //  return All((Convertible<Argssize_t>() || Same<Args, slice>())...)
  //    && Some(Same<Args, slice>()...);
  //}

  template<typename List>
  bool check_non_jagged(const List& list);

  template<size_t N, typename I, typename List>
  Enable_if<(N == 1), void> add_extents(I& first, const List& list);

  template<size_t N, typename I, typename List>
  Enable_if<(N > 1), void> add_extents(I& first, const List& list);

  template<size_t N, typename List>
  std::array<size_t, N> derive_extents(const List& list);

  template<typename T, typename Vec>
  void add_list(const T* first, const T* last, Vec& vec);

  template<typename T, typename Vec>
  void add_list(const std::initializer_list<T>* first, const std::initializer_list<T>* last, Vec& vec);

  template<typename T, typename Vec>
  void insert_flat(std::initializer_list<T> list, Vec& vec);

} // namespace Matrix_impl 

namespace Matrix_impl {

  //template<size_t N, typename... Dims>
  //bool check_bounds(const Matrix_slice<N>& slice, Dims... dims)
  //{
  //  size_t indexes[N]{ size_t(dims)... };
  //  return equal(indexes, indexes + N, slice.extents, less<size_t>{});
  //}

  template<typename... Args>
  constexpr bool Requesting_element()
  {
    //return All(Convertible<Args, size_t>()...);
    return true;
  }

  //constexpr bool All() { return true; }

  //template<typename... Args>
  //constexpr bool All(bool b, Args...args)
  //{
  //  return b && All(args...);
  //}

  //template<typename... Args>
  //constexpr bool Requesting_slice()
  //{
  //  return All((Convertible<Argssize_t>() || Same<Args, slice>())...)
  //    && Some(Same<Args, slice>()...);
  //}
  template<typename List>
  bool check_non_jagged(const List& list)
  {
    auto i = list.begin();
    for (auto j = i + 1; j != list.end(); ++j)
      if (i->size() != j->size())
        return false;
    return true;
  }

  template<size_t N, typename I, typename List>
  Enable_if<(N == 1), void> add_extents(I& first, const List& list)
  {
    *first++ = list.size();
  }

  template<size_t N, typename I, typename List>
  Enable_if<(N > 1), void> add_extents(I& first, const List& list)
  {
    assert(check_non_jagged(list));
    *first = list.size();
    add_extents<N - 1>(++first, *list.begin());
  }

  template<size_t N, typename List>
  std::array<size_t, N> derive_extents(const List& list)
  {
    std::array<size_t, N> a;
    auto f = a.begin();
    add_extents<N>(f, list); // put extents from list into f[]
    return a;
  }

  template<typename T, typename Vec>
  void add_list(const T* first, const T* last, Vec& vec)
  {
    vec.insert(vec.end(), first, last);
  }

  template<typename T, typename Vec>
  void add_list(const std::initializer_list<T>* first, const std::initializer_list<T>* last, Vec& vec)
  {
    for (; first != last; ++first) {
      add_list(first->begin(), first->end(), vec);
      //auto sss = first->begin();
      //int a = 10;
    }
  }

  template<typename T, typename Vec>
  void insert_flat(std::initializer_list<T> list, Vec& vec)
  {
    add_list(list.begin(), list.end(), vec);
  }

} // namespace Matrix_impl