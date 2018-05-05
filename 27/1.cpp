#include <iostream>

class Shape {

};

class Circle : public Shape {


};


template<typename T>
class Ptr {
  T* p;
public:
  Ptr(T*);
  Ptr(const Ptr&);
  template<typename T2>
    explicit operator Ptr<T2>();
};

template<typename T>
Ptr<T>::Ptr(T* pp):p(pp) {}

template<typename T>
Ptr<T>::Ptr(const Ptr<T>&) {}

template<typename T>
  template<typename T2>
    Ptr<T>::operator Ptr<T2>()
    {
      return Ptr<T2>{p};
    }



void f(Ptr<Circle> pc)
{
  Ptr<Shape> ps{pc};
  //Ptr<Circle> pc2{ps}; // error
}

int main() {



  return 0;
}