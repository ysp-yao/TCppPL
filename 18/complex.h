#ifndef COMPLEX_H_
#define COMPLEX_H_

class complex {
  double re, im;
public:
  complex& operator+=(complex a);

  constexpr complex(double r=0, double i=0):re{r}, im{i} {}
};

// complex operator+(complex a, complex b) {
//   return a+=b;
// }


#endif // COMPLEX_H_
