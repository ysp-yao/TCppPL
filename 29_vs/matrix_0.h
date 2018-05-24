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