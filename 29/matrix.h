#include <vector>
#include <array>
#include <cstddef>
#include <type_traits>
#include <iostream>
#include <cassert>

using namespace std;

template<bool B, typename T>
using Enable_if = typename std::enable_if<B, T>::type;

struct slice;
template<size_t N>
struct Matrix_slice;
template<typename T, size_t N>
class Matrix_ref;
template<typename T, size_t N>
class Matrix;




namespace Matrix_impl {

  template<typename T, size_t N>
  struct Matrix_init {
    using type = initializer_list<typename Matrix_init<T, N - 1>::type>;
  };

  template<typename T>
  struct Matrix_init<T, 1> {
    using type = initializer_list<T>;
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
  Enable_if<(N > 1), void> add_extents(I& first, const List& list)
  {
    assert(check_non_jagged(list));
    *first = list.size();
    add_extents<N - 1>(++first, *list.begin());
  }

  template<size_t N, typename I, typename List>
  Enable_if<(N == 1), void> add_extents(I& first, const List& list)
  {
    *first++ = list.size();
  }

  template<size_t N, typename List>
  array<size_t, N> derive_extents(const List& list)
  {
    array<size_t, N> a;
    auto f = a.begin();
    add_extents<N>(f, list); // put extents from list into f[]
    return a;
  }


  template<typename T, typename Vec>
  void add_list(const std::initializer_list<T>* first, const std::initializer_list<T>* last, Vec& vec)
  {
    for (; first!=last; ++first)
      add_list(first−>begin(), first−>end(), vec);
  }

  template<typename T, typename Vec>
  void add_list(const T* first, const T* last, Vec& vec)
  {
    vec.insert(vec.end(), first, last);
  }

  template<typename T, typename Vec>
  void insert_flat(initializer_list<T> list, Vec& vec)
  {
    add_list(list.begin(), list.end(), vec);
  }

} // namespace Matrix_impl



struct slice {
  slice():start(-1),length(-1),stride(-1) {}
  explicit slice(size_t s):start(s),length(-1),stride(1) {}
  slice(size_t s, size_t l, size_t n=1):start(s),length(l),stride(n) {}
  
  size_t operator()(size_t i) const { return start+i*stride; }
  
  static slice all; 
  
  size_t start; // 第一个索引
  size_t length; // 包含的索引数目（可用于范围检查）
  size_t stride; // 序列中元素间的距离
};
  
template<size_t N>
struct Matrix_slice {
  Matrix_slice() = default; // an empty matrix: no elements
  Matrix_slice(size_t s, initializer_list<size_t> exts); // extents
  Matrix_slice(size_t s, initializer_list<size_t> exts, initializer_list<size_t> strs);// extents and strides

  template<typename...Dims> //N extents
    Matrix_slice(Dims... dims);

  //template<typename... Dims,
  //  typename = Enable_if<All(Convertible<Dims, size_t>()...)> >
  //  size_t operator()(Dims... dims) const; // calculate index from a set of subscripts

  size_t size; // total number of elements
  size_t start; // starting offset
  array<size_t, N> extents; // number of elements in each dimension
  array<size_t, N> strides; // offsets between elements in each dimension
};

//template<typename... Dims>
//size_t Matrix_slice<N>::operator()(Dims... dims) const
//{
//  static_assert(sizeof...(Dims)==N, "");
//  size_t args[N]{ size_t(dims)... };
//  return inner_product(args, args+N, strides.begin(), size_t(0));
//}


template<typename T, size_t N>
class Matrix_base {
  // ...公共内容...

};
  
template<typename T, size_t N>
class Matrix_ref : public Matrix_base<T,N> {
    // ...Matrix_ref特有内容...
private:
  Matrix_slice<N> desc; // 矩阵形状
  T* ptr;
};





template<typename T, size_t N>
using Matrix_initializer = typename Matrix_impl::Matrix_init<T, N>::type;


template<typename T, size_t N>
class Matrix : public Matrix_base<T,N> {
public:
  static constexpr size_t order = N;
  using value_type = T;
  using iterator = typename std::vector<T>::iterator;
  using const_iterator = typename std::vector<T>::const_iterator;

  Matrix(Matrix_initializer<T, N> init);

  //Matrix() = default;
  Matrix() { 
    std::cout << "Matrix()\n"; 
  }

  //Matrix(Matrix&&) = default;
  //Matrix& operator=(Matrix&&) = default;
  //Matrix(Matrix const&) = default;
  //Matrix& operator=(Matrix const&) = default;
  //~Matrix() = default;

  //template<typename U>
  //  Matrix(const Matrix_ref<U, N>&);  
  //template<typename U>
  //  Matrix& operator=(const Matrix_ref<U, N>&);

  template<typename... Exts>
    explicit Matrix(Exts... exts);  

  //Matrix(Matrix_initializer<T, N>);
  //Matrix& operator=(Matrix_initializer<T, N>);

  //template<typename U>
  //  Matrix(initializer_list<U>) = delete;
  //template<typename U>
  //  Matrix& operator=(initializer_list<U>) = delete;

  //static constexpr size_t order() { return N; } //  维数
  //size_t extent(size_t n) const { return desc.extents[n]; } //  第n维元素数
  //size_t size() const { return elems.size(); }  //  元素总数
  //const Matrix_slice<N>& descriptor() const { return desc; }  //  

  T* data() { return elems.data(); }
  const T* data() const { return elems.data(); }
  //
  //
  // 29.2.2 下标和切片
  //
  template<typename... Args>
    Enable_if<Matrix_impl::Requesting_element<Args...>(), T&>
    operator()(Args... args);
  //template<typename... Args>
  //  enable_if<Matrix_impl::Requesting_element<Args...>(), const T&>
  //  operator()(Args... args) const;
  //template<typename... Args>
  //  enable_if<Matrix_impl::Requesting_slice<Args...>(), Matrix_ref<T,N>>
  //  operator()(const Args&... args);
  //template<typename... Args>
  //  enable_if<Matrix_impl::Requesting_slice<Args...>(), Matrix_ref<const T,N>>
  //  operator()(const Args&... args) const;

  Matrix_ref<T,N-1> operator[](size_t i) { return row(i); }
  Matrix_ref<const T,N-1> operator[](size_t i) const { return row(i); }

  Matrix_ref<T, N - 1> row(size_t n);
  Matrix_ref<const T,N-1> row(size_t n) const;

  Matrix_ref<T,N-1> col(size_t n);
  Matrix_ref<const T,N-1> col(size_t n) const;

private:
  Matrix_slice<N> desc; // 定义N个维度大小的切片
  std::vector<T> elems; // 元素
};


//
//template<typename T, size_t N>
//Matrix_ref<T, N-1> Matrix<T,N>::row(size_t n)
//{
//  assert(n<rows());
//  Matrix_slice<N - 1> row;
//  Matrix_impl::slice_dim<0>(n, desc, row);
//  return { row,data() };
//}
//template<typename T>
//T& Matrix<T,1>::row(size_t i)
//{
//  return &elems[i];
//}
//
//template<typename T>
//T& Matrix<T, 0>::row(size_t n) = delete;
//
//template<typename T, size_t N>
//Matrix_ref<T, N - 1> Matrix<T, N>::col(size_t n) {
//  assert(n<cols());
//  Matrix_slice<N - 1> col;
//  Matrix_impl::slice_dim<1>(n, desc, col);
//  return { col,data() };
//}

template<typename T, size_t N>
  template<typename... Args>
  Enable_if<Matrix_impl::Requesting_element<Args...>(), T&>
    Matrix<T, N>::operator()(Args... args)
  {
    //assert(Matrix_impl::check_bounds(desc, args...));
    //return *(data() + desc(args...));
    T a;
    return a;
  }



template<typename T>
class Matrix<T, 0> {
public:
  static constexpr size_t order = 0;
  using value_type = T;

  Matrix(const T& x) :elem(x) {}
  Matrix& operator=(const T& value) { elem = value; return *this; }

  T& operator()() { return elem; }
  const T& operator()() const { return elem; }

  operator T&() { return elem; } // ?????
  operator const T&() const { return elem; } // ?????
private:
  T elem;
};
//
// 二元+、-、*运算定义为非成员函数
//
//template<typename T, size_t N>
//Matrix<T,N> operator+(const Matrix<T,N>& m, const T& val) {
//  Matrix<T,N> res = m;
//  res += val;
//  return res;
//}
//
//template<typename T, size_t N>
//Matrix<T,N> operator+(const Matrix<T,N>& a, const Matrix<T,N>& b) {
//  Matrix<T,N> res = a;
//  res += b;
//  return res;
//}
//
//template<typename T,typename T2,size_t N,
//        typename RT=Matrix<Common_type<Value_type<T>,Vlaue_type<T2>>,N>
//Matrix<RT,N> operator+(const Matrix<T,N>& a, const Matrix<T2,N>& b) 
//{
//  Matrix<RT,N> res = a;
//  res += b;
//  return res;
//}
//
//template<typename T, size_t N>
//Matrix<T,N> operator+(const Matrix<T,N>& x, const T& n) {
//  Matrix<T,N> res = x;
//  res += n;
//  return res;
//}

//
// 输出函数
//
//template<typename M>
//enable_if<Matrix_type<M>(), ostream&>
//operator<<(ostream& os, const M& m) {
//  os << '{';
//  for (size_t i=0; i!=rows(m); ++i) {
//    os << m[i];
//    if (i+1!=rows(m)) os << ',';
//  }
//  return os << '}';
//}




// constructors
template<typename T, size_t N>
Matrix<T, N>::Matrix(Matrix_initializer<T, N> init) {


  //Matrix_impl::derive_extents<N>(init);

  desc.extents = Matrix_impl::derive_extents<N>(init);
  elems.reserve(desc.size);
  Matrix_impl::insert_flat(init, elems);
  std::cout << "Matrix(Matrix_initializer<T, N> init) : " << elems.size() << "\n";
  assert(elems.size() == desc.size);
}

template<typename T, size_t N>
  template<typename... Exts>
  Matrix<T,N>::Matrix(Exts... exts)
    :desc{exts...},
      elems(desc.size)
  {}


