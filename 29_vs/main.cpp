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
  // N == 2 ，从特殊化到泛化
  //
  // 29.3.1 构造和赋值
  //Matrix<int, 2> m1(2, 2); //
  Matrix<int, 2> m2{ {1,2,3},{11,12,13} }; //
  //Matrix_ref<int, 2> mf;
  //Matrix<int, 2> m3(mf); // error
  //Matrix<int, 2> m4;
  //m4 = mf; //

  Matrix_ref<int, 1> mf1 = m2[0];




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
  //m2[0];
}