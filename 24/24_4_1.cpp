#include <iostream>

template<typename T>
bool Copy_assign_equality(T x, T& y)
{
  return (y=x, y==x);
}

int main() {
  int a = 10;
  int b = 10;
  //Copy_assign_equality<int>(a,b);
  std::cout << Copy_assign_equality(a, b) << std::endl;

}