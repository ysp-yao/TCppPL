#include "complex.h"

inline complex& complex::operator+=(complex a) {
  re += a.re;
  im += a.im;
  return *this;
}