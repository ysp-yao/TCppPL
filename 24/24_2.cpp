#include <iostream>
#include  <functional>

template<typename Iter, typename Val>
Val sum(Iter first, Iter last)
{
  Val s = 0;
  while (first!=last) {
    s = s + *first;
    ++first;
  }
  return s;
}

template<typename Iter, typename Val>
Val accumulate(Iter first, Iter last, Val s)
{
  while (first!=last) {
    s = s + *first;
    ++first;
  }
  return s;
}

template<typename Iter, typename Val, typename Oper>
Val accumulate(Iter first, Iter last, Val s, Oper op)
{
  while (first != last) {
    s = op(s, *first);
    ++first;
  }
  return s;
}


//struct Node { Node* next; int data; };
//Node* operator++(Node* p) { return p->next; }
//int operator*(Node* p) { return p->data; }
//Node* end(lst) { return nullptr; }


//int main() {
//  double ad[] = {1,2,3,4};
//  // double s = sum(ad, ad + 4); // error
//  // double s = sum<double*>(ad, ad + 4); //  error
//  double s = sum<double*, double>(ad, ad+4);
//  std::cout << s << std::endl;
//
//  double s1 = accumulate(ad,ad+4,0.0);
//  double s2 = accumulate(ad, ad + 4, 0);
//  std::cout << s1 << std::endl;
//  std::cout << s2 << std::endl;
//
//  double s3 = accumulate(ad, ad+4, 0.0, std::plus<double>());
//  std::cout << s3 << std::endl;
//
//}