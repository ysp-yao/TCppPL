//#include <cstdlib>
//#include <iostream>
//
//template<typename F>
//struct Final_action {
//  Final_action(F f) :clean{ f } {}
//  ~Final_action() { clean(); }
//  F clean;
//};
//
//template<class F>
//Final_action<F> finally(F f)
//{
//  return Final_action<F>(f);
//}
//
//void test() 
//{
//  int* p = new int{ 7 };
//  int* buf = (int*)malloc(100*sizeof(int));
//
//  auto act1 = finally([&] {
//                  delete p;
//                  free(buf);
//                  std::cout << "Goodby, Cruel world!\n";
//                });
//
//  int var = 0;
//  std::cout << "var=" << var << '\n';
//
//  {
//    var = 1;
//    auto act2 = finally([&] {std::cout << "finally!\n"; var = 7; });
//    std::cout << "var=" << var << '\n';
//  }
//
//  std::cout << "var=" << var << '\n';
//}
//
//int main() {
//
//  test();
//
//  return 0;
//}