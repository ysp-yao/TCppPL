#include "matrix.h"

#include <iostream>

int main() {

  //
  // N == 0
  //
  // Matrix<double, 0> m0{1};

  //
  // N == 1
  //
  // Matrix<double, 1> m1{ 1,2, 3,4 };

  //
  // N > 1
  //
  Matrix<int, 2> m2{ {1,2,3},{11,12,13} };
  //std::cout << m1.order() <<std::endl;
  //std::cout << m2.order() << std::endl;
  //std::cout << m1.extent(0) << std::endl;
  //std::cout << m1.extent(1) << std::endl;
  //std::cout << m2.extent(0) << std::endl;
  //std::cout << m2.extent(1) << std::endl;
  //std::cout << m1.size() << std::endl;
  //std::cout << m2.size() << std::endl;

  //Matrix<int, 2> mm2(5,6);
  //Matrix<int, 2> mm3{ 5, 6 }; //error


  //m2(1, 2) = 99;
  //m2(1, 2);
  m2[0];
}