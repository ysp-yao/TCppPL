struct slice {
  slice():start(-1),length(-1),stride(-1) {}
  explicit slice(size_t s):start(s),length(-1),stride(1) {}
  slice(size_t s, size_t l, size_t n=1):start(s),length(l),stride(n) {}

  size_t operator()(size_t i) const { return start+i*stride; }

  static slice all; 

  size_t start;
  size_t length;
  size_t stride;
};

template<size_t N>
struct Matrix_slice {
  Matrix_slice() = default;

  Matrix_slice(size_t s, initializer_list<size_t> exts);
  Matrix_slice(size_t s, initializer_list<size_t> exts, initialzer_list<size_t> strs);

  template<typename... Dims>
    Matrix_slice(Dims... dims);

  template<typename... Dims,
           typename=Enable_if<All(Convertible<Dims.size_t>()...)> >

  size_t size;
  size_t start;
  array<size_t,N> extents;
  array<size_t,N> strides;
};

template<typename... Dims>
size_t Matrix_slice<N>::operator()(Dims... dims) const
{
  // static_assert();
}

template<typename T, size_t N>
class Matrix_ref {
public:
  Matrix_ref(const Matrix_slice<N>& s, T* p):desc{s}, ptr{p} {}
private:
  Matrix_slice<N> desc;
  T* ptr;
};



template<typename T, size_t N>
class Matrix {
public:
  static constexpr size_t order = N;
  using value_type = T;
  using iterator = typename std::vector<T>::iterator;
  using const_iterator = typename std::vector<T>::const_iterator;

  Matrix() = default;
  Matrix(Matrix&&) = default;
  Matrix& operator=(Matrix&&) = default;
  Matrix(Matrix const&) = default;
  Matrix& operator=(Matrix const&) = default;
  ~Matrix() = default;

  template<typename U>
    Matrix(const Matrix_ref<U, N>&);  
  template<typename U>
    Matrix& operator=(const Matrix_ref<U, N>&);

  template<typename... Exts>
    explicit Matrix(Exts... exts);  

  Matrix(Matrix_initializer<T, N>);
  Matrix& operator=(Matrix_initializer<T, N>);

  template<typename U>
    Matrix(initializer_list<U>) = delete;
  template<typename U>
    Matrix& operator=(initializer_list<U>) = delete;

  static constexpr size_t order() { return N; } //  维数
  size_t extent(size_t n) const { return desc.extents[n]; } //  第n维元素数
  size_t size() const { return elems.size(); }  //  元素总数
  const Matrix_slice<N>& descriptor() const { return desc; }  //  

  T* data() { return elems.data(); }
  const T* data() const { return elems.data(); }
  
  //
  // 下标和切片
  //
  template<typename... Args>
    Enable_if<Matrix_impl::Requesting_element<Args...>(), T&>
    operator()(Args... args);
  template<typename... Args>
    Enable_if<Matrix_impl::Requesting_element<Args...>(), const T&>
    operator()(Args... args) const;
  template<typename... Args>
    Enable_if<Matrix_impl::Requesting_slice<Args...>(), Matrix_ref<T,N>>
    operator()(const Args&... args);
  template<typename... Args>
    Enable_if<Matrix_impl::Requesting_slice<Args...>(), Matrix_ref<const T,N>>
    operator()(const Args&... args) const;

  Matrix_ref<T,N-1> operator[](size_t i) { return row(i); }
  Matrix_ref<const T,N-1> operator[](size_t i) const { return row(i); }

  Matrix_ref<T,N-1> row(size_t n);
  Matrix_ref<const T,N-1> row(size_t n) const;

  Matrix_ref<T,N-1> col(size_t n);
  Matrix_ref<const T,N-1> col(size_t n) const;

  //
  // 算数运算
  //
  template<typename F>
    Matrix& apply(F f);
  
  template<typename M, typename F>
    Matrix& apply(const M& m, F f);

  Matrix& operator=(const T& value);

  Matrix& operator+=(const T& value);
  Matrix& operator-=(const T& value);
  Matrix& operator*=(const T& value);
  Matrix& operator/=(const T& value);
  Matrix& operator%=(const T& value);
  
  template<typename M>
    Matrix& operator+=(const M& x);
  template<typename M>
    Matrix& operator-=(const M& x);
    

private:
  Matrix_slice<N> desc;
  vector<T> elems;
};

//
// 二元+、-、*运算定义为非成员函数
//
template<typename T, size_t N>
Matrix<T,N> operator+(const Matrix<T,N>& m, const T& val) {
  Matrix<T,N> res = m;
  res += val;
  return res;
}

template<typename T, size_t N>
Matrix<T,N> operator+(const Matrix<T,N>& a, const Matrix<T,N>& b) {
  Matrix<T,N> res = a;
  res += b;
  return res;
}

template<typename T,typename T2,size_t N,
        typename RT=Matrix<Common_type<Value_type<T>,Vlaue_type<T2>>,N>
Matrix<RT,N> operator+(const Matrix<T,N>& a, const Matrix<T2,N>& b) 
{
  Matrix<RT,N> res = a;
  res += b;
  return res;
}

template<typename T, size_t N>
Matrix<T,N> operator+(const Matrix<T,N>& x, const T& n) {
  Matrix<T,N> res = x;
  res += n;
  return res;
}

//
// 输出函数
//
template<typename M>
Enable_if<Matrix_type<M>(), ostream&>
operator<<(ostream& os, const M& m) {
  os << '{';
  for (size_t i=0; i!=rows(m); ++i) {
    os << m[i];
    if (i+1!=rows(m)) os << ',';
  }
  return os << '}';
}