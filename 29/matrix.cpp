//#include "matrix.h"

//namespace Matrix_impl {
  
  //
  //template<typename T, size_t N>
  //  template<typename... Exts>
  //  Matrix<T,N>::Matrix(Exts... exts)
  //    :desc{exts...},
  //     elems(desc.size)
  //  {}
  //
  //template<typename T, size_t N>
  //Matrix<T, N>::Matrix(Matrix_initializer<T, N> init) {
  //  std::cout << "Matrix(Matrix_initializer<T, N> init)\n";

    //Matrix_impl::derive_extents(init, desc.extents);
    //elems.reserve(desc.size);
    //Matrix_impl::insert_flat(init, elems);
    //assert(elems.size() == desc.size);
  //}
  //
  //template<typename T, size_t N>
  //  template<typename U>
  //  Matrix<T,N>::Matrix(const Matrix_ref<U,N>& x)
  //    :desc{x.desc}, elems{x.begin(),x.end()}
  //{
  //  static_assert(Convertible<U,T>(), "Matrix constructor: incompatible element types");
  //}
  //
  //template<typename T, size_t N>
  //  template<typename U>
  //  Matrix<T,N>& Matrix<T,N>::operator=(const Matrix_ref<U,N>& x)
  //{
  //  static_assert(Convertible<U,T>(), "Matrix =: incompatible element types");
  //  
  //  desc = x.desc;
  //  elems.assign(x.begin(), x.end());
  //  return *this;
  //}
  //
  //  //
  //  // 下标和切片
  //  //
  //  template<typename... Args>
  //    enable_if<Matrix_impl::Requesting_element<Args...>(), T&>
  //    operator()(Args... args);
  //  template<typename... Args>
  //    enable_if<Matrix_impl::Requesting_element<Args...>(), const T&>
  //    operator()(Args... args) const;
  //  template<typename... Args>
  //    enable_if<Matrix_impl::Requesting_slice<Args...>(), Matrix_ref<T,N>>
  //    operator()(const Args&... args);
  //  template<typename... Args>
  //    enable_if<Matrix_impl::Requesting_slice<Args...>(), Matrix_ref<const T,N>>
  //    operator()(const Args&... args) const;
  //
  //  Matrix_ref<T,N-1> operator[](size_t i) { return row(i); }
  //  Matrix_ref<const T,N-1> operator[](size_t i) const { return row(i); }
  //
  //  Matrix_ref<T,N-1> row(size_t n);
  //  Matrix_ref<const T,N-1> row(size_t n) const;
  //
  //  Matrix_ref<T,N-1> col(size_t n);
  //  Matrix_ref<const T,N-1> col(size_t n) const;
  //
  //
  ////
  //// 算数运算
  ////
  //template<typename T, size_t N>
  //  template<typename F>
  //  Matrix<T,N>& Matrix<T,N>::apply(F f)
  //  {
  //    for (auto& x:elems) f(x);
  //    return *this;
  //  }
  //
  //template<typename T, size_t N>
  //  template<typename M, typename F>
  //  enable_if<Matrix_type<M>(),Matrix<T,N>&> Matrix<T,N>::apply(const M& m, F f)
  //  {
  //    assert(same_extents(desc, m.descriptor()));
  //    for (auto i=begin(),j=m.begin(); i!=end(); ++i,++j)
  //      f(*i, *j);
  //    reutrn *this;
  //  } 
  //
  //Matrix& operator=(const T& value);
  //
  //template<typename T, size_t N>
  //Matrix<T,N>& Matrix<T,N>::operator+=(const T& val) {
  //  return apply([&](T& a){ a+=val; });
  //}
  //
  //Matrix& operator-=(const T& value);
  //Matrix& operator*=(const T& value);
  //Matrix& operator/=(const T& value);
  //Matrix& operator%=(const T& value);
  //
  //template<typename T, size_t N>
  //  template<typename M>
  //  enable_if<Matrix_type<M>(),Matrix<T,N>&> Matrix<T,N>::operator+=(const M& x) 
  //  {
  //    static_assert(m.order()==N, "+=: mismatched Matrix dimensions");
  //    assert(same_extents(desc, m.descriptor()));
  //
  //    return apply(m, [](T& a, Value_type<M>&b){ a+=b; });
  //  }
  //
  //template<typename M>
  //  Matrix& operator-=(const M& x);

//} // namespace Matrix_impl