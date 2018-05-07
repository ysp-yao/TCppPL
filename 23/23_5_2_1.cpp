//#include <iostream>
//#include <memory>
//#include <utility>
//
//template<typename T>
//class Xref {
//public:
//  Xref(int i, T* p)
//    :index{i}, elem{ p }, owned{ true }
//  {
//    std::cout << "1\n";
//  }
//
//  Xref(int i, T& r)
//    :index{ i }, elem{ &r }, owned{ false }
//  {
//    std::cout << "2\n";
//  }
//
//  Xref(int i, T&& r)
//    :index{ i }, elem{ new T{move(r)} }, owned{ true }
//  {
//    std::cout << "3\n";
//  }
//
//  ~Xref()
//  {
//    if (owned) delete elem;
//  }
//private:
//  int index;
//  T* elem;
//  bool owned;
//};
//
//template<typename TT, typename A>
//std::unique_ptr<TT> make_unique(int i, A&& a)
//{
//  return std::unique_ptr<TT>{new TT{i, std::forward<A>(a)}};
//}

//int main() {
//
//  std::string x{"There and back again"};
//
//  Xref<std::string> r1{7, "Here"};
//  Xref<std::string> r2{ 9, x };
//  Xref<std::string> r3{ 3, new std::string("There") };
//
//  auto p1 = make_unique<Xref<std::string>>(7, "Here");
//  auto p2 = make_unique<Xref<std::string>>(9, x);
//
//}