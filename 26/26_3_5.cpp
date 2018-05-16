#include <iostream>
using namespace std;

namespace N {
  class A {};
  char f(A) { cout << "N::f(A)\n"; }
}

char f(int) { cout << "f(int)\n"; }

template<typename T>
char g(T t)
{
  return f(t);
}

char f(double) { cout << "f(double)\n"; }


char c1 = g(N::A());
char c2 = g(2);
char c3 = g(2.1);

int main()
{
  return 0;
}