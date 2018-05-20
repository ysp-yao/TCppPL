#include "matrix.h"

#include <iostream>

int main() {
  std::cout << "mmm\n";

  Matrix<double, 0> m0{1};
  Matrix<double, 1> m1{1,2, 3,4};
  Matrix<int, 2> m2{ {1,2,3},{11,12,13} };
  //m2(1, 2) = 99;
  //m2(1, 2);


}