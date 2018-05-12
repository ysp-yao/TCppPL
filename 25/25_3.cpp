//
// https://blog.csdn.net/armman/article/details/1547056?locationNum=8&fps=1
//

#include <iostream>
#include <typeinfo>

template<typename T>
class Vector {
public:
  Vector() { std::cout << typeid(T).name() << "\n";}
};

template<>
class Vector<void*> { // 完整特例化
public:
  Vector() { 
    //std::cout << "void*\n"; 
    std::cout << "void*  ";
  }
};

template<typename T>
class Vector<T*>:public Vector<void*> {// 部分特例化
public:
  Vector() { 
    std::cout << typeid(T).name() << "\n";
  }
};

class Node {

};

  int main() {
    Vector<int> v1;
    Vector<int*> v2;
    Vector<double> v3;
    Vector<double*> v4;
    Vector<Node> v5;
    Vector<Node*> v6;
    Vector<void*> v7;

  }