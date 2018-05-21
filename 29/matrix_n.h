#include <vector>
#include <array>
#include <cstddef>

#include <iostream>
#include <cassert>

using namespace std;



struct slice;
template<size_t N>
struct Matrix_slice;
template<typename T, size_t N>
class Matrix_ref;
template<typename T, size_t N>
class Matrix;





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
  Matrix_slice(size_t s, initializer_list<size_t> exts) { // extents
    int a = 10;
  }
  Matrix_slice(size_t s, initializer_list<size_t> exts, initializer_list<size_t> strs) {// extents and strides
    int a = 10;

  }
  template<typename...Dims> //N extents
  Matrix_slice(Dims... dims):
    extents{size_t(dims)...}
  {
    int a = 10;
    
    }

  //template<typename... Dims,
  //  typename = Enable_if<All(Convertible<Dims, size_t>()...)> >
  //  size_t operator()(Dims... dims) const; // calculate index from a set of subscripts

  size_t size; // total number of elements
  size_t start; // starting offset
  array<size_t, N> extents; // number of elements in each dimension, 比如[2, 3]表示一个2x3的矩阵
  array<size_t, N> strides; // offsets between elements in each dimension
};

//template<typename... Dims>
//size_t Matrix_slice<N>::operator()(Dims... dims) const
//{
//  static_assert(sizeof...(Dims)==N, "");
//  size_t args[N]{ size_t(dims)... };
//  return inner_product(args, args+N, strides.begin(), size_t(0));
//}

//template<>
//struct Matrix_slice<1> {
//  size_t operator()(size_t i) const
//  {
//    return i;
//  }
//};
//
//template<>
//struct Matrix_slice<2> {
//  size_t operator()(size_t i, size_t j) const
//  {
//    return 1;
//  }
//};


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
  //static constexpr size_t order = N;
  using value_type = T;
  using iterator = typename std::vector<T>::iterator;
  using const_iterator = typename std::vector<T>::const_iterator;

  Matrix(Matrix_initializer<T, N> init);

  Matrix() = default;


  //Matrix(Matrix&&) = default;
  //Matrix& operator=(Matrix&&) = default;
  //Matrix(Matrix const&) = default;
  //Matrix& operator=(Matrix const&) = default;
  //~Matrix() = default;

  template<typename U>
    Matrix(const Matrix_ref<U, N>&);  
  template<typename U>
    Matrix& operator=(const Matrix_ref<U, N>&);

  template<typename... Exts>
    explicit Matrix(Exts... exts);  // 指明每一维大小

  template<typename U>
    Matrix(initializer_list<U>) = delete;
  template<typename U>
    Matrix& operator=(initializer_list<U>) = delete;

  //Matrix(Matrix_initializer<T, N>);
  //Matrix& operator=(Matrix_initializer<T, N>);

  //template<typename U>
  //  Matrix(initializer_list<U>) = delete;
  //template<typename U>
  //  Matrix& operator=(initializer_list<U>) = delete;

  static constexpr size_t order() { return N; } //  维数
  size_t extent(size_t n) const { return desc.extents[n]; } //  第n维元素数
  size_t size() const { return elems.size(); }  //  元素总数
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

  Matrix_ref<T, N - 1> row(size_t n) {
    //assert(n<rows());
    //Matrix_slice<N - 1> row;
    //Matrix_impl::slice_dim<0>(n,desc,row);
    //return {row,data()};
    return Matrix_ref<T, N - 1>();
  }
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




// constructors
template<typename T, size_t N>
Matrix<T, N>::Matrix(Matrix_initializer<T, N> init) {
  desc.extents = Matrix_impl::derive_extents<N>(init); // 应该重载复制操作符=
  elems.reserve(desc.size);
  Matrix_impl::insert_flat(init, elems);
  std::cout << "Matrix(Matrix_initializer<T, N> init) : " << elems.size() << "\n";
  //assert(elems.size() == desc.size);
}

template<typename T, size_t N>
  template<typename... Exts>
  Matrix<T,N>::Matrix(Exts... exts)
    :desc{exts...},
      elems(desc.size)
  {
    std::cout << "Matrix(Exts... exts)";
  }

template<typename T, size_t N>
  template<typename U>
  Matrix<T, N>::Matrix(const Matrix_ref<U, N>& x)
    :desc{ x.desc }, elems{x.begin(), x.end()}
  {
    static_assert(Convertible<U,T>(), "Matrix constructor: incompatible element types");
  }

template<typename T, size_t N>
  template<typename U>
  Matrix<T, N>& Matrix<T, N>::operator=(const Matrix_ref<U, N>& x)
  {
    static_assert(Convertible<U, T>(), "Matrix =: incompatible element types");
    desc = x.desc;
    elems.assign(x.begin(), x.end());
    return *this;
  }


//
// 输出函数
//
//template<typename M>
//Enable_if<Matrix_type<M>(), ostream&>
//operator<<(ostream& os, const M& m) {
//  os << '{';
//  for (size_t i=0; i!=rows(m); ++i) {
//    os << m[i];
//    if (i+1!=rows(m)) os << ',';
//  }
//  return os << '}';
//}