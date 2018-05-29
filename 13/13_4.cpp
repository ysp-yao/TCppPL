//#include  <stdexcept>
//#include <string>
//#include <sstream>
//#include <iostream>
//enum class Mode;
//
//#define CURRENT_MODE Mode::throw_ // 编译器选项
//#define CURRENT_LEVEL 1 // 编译器选项
//
//#define max 10
//
//
//namespace Assert {
//  enum class Mode { throw_, terminate_, ignore_};
//  constexpr Mode current_mode = CURRENT_MODE;
//  constexpr int current_level = CURRENT_LEVEL;
//  constexpr int default_level = 1;
//
//  constexpr bool level(int n) {
//    return n <= current_level;
//  }
//
//  struct Error :std::runtime_error {
//    Error(const std::string& p) :runtime_error(p) {}
//  };
//
//  std::string compose(const char* file, int line, const std::string& message) {
//    std::ostringstream os("(");
//    os << file << "," << line << "):" << message;
//    return os.str();
//  }
//
//  template<bool condition=level(default_level), class Except=Error>
//  void dynamic(bool assertion, const std::string& message="Assert::dynamic failed")
//  {
//    if (assertion) return;
//    if (current_mode == Mode::throw_) throw Except{message};
//    if (current_mode == Mode::terminate_) std::terminate();
//  }
//
//  template<>
//  void dynamic<false, Error>(bool, const std::string&) {
//  }
//
//  void dynamic(bool b, const std::string& s) {
//    dynamic<true, Error>(b,s);
//  }
//
//  void dynamic(bool b) {
//    dynamic<true, Error>(b);
//  }
//}
//
////void f(int n) {
////  Assert::dynamic<Assert::level(2), Assert::Error>((n <= 0 || max < n), Assert::compose(__FILE__, __LINE__, "range problem"));
////}
//
//void f(int n) {
//  Assert::dynamic((n <= 0 || max < n), Assert::compose(__FILE__, __LINE__, "range problem"));
//}
//
//
//int main() {
//  try {
//    f(5);
//  }
//  catch(Assert::Error e) {
//    std::cout << e.what() << std::endl;
//  }
//}