#include "string.h"

//#include <cstring>

void String::copy_from(const String& x) 
{
  if (x.sz <= short_max) {
    memcpy(this, &x, sizeof(x));
    ptr = ch;
  }
  else {
    ptr = expand(x.ptr, x.sz+1);
    sz = x.sz;
    space = 0;
  }
}

void String::move_from(String& x) 
{
  if (x.sz <= short_max) {
    memcpy(this, &x, sizeof(x));
    ptr = ch;
  }
  else {
    ptr = x.ptr;
    sz = x.sz;
    space = x.space;
    x.ptr = x.ch;
    x.sz = 0;
    x.ch[0] = 0;
  }
}

String::String()
          :sz{0}, ptr{ch}
{
  ch[0] = 0;
}

String::String(const char* p):
          sz{strlen(p)},
          ptr{(sz<=short_max)?ch:new char[sz+1]},
          space{0}
{
  std::cout << "String(const char* p)\n";
  strcpy(ptr, p);
}

String::String(const String& x)
{
  std::cout << "String(const String& x)\n";
  copy_from(x);  
}

String::String(String&& x)
{
  std::cout << "String(String&& x)\n";
  move_from(x);  
}

String& String::operator=(const String& x)
{
  std::cout << "operator=(const String& x)\n";
  if (this==&x) return *this;
  char* p = (short_max<sz)?ptr:0;
  copy_from(x);
  delete[] p;
  return *this;
}

String& String::operator=(String&& x)
{
  std::cout << "operator=(String&& x)\n";
  if (this==&x) return *this;
  if (short_max<sz) delete[] ptr;
  move_from(x);
  return *this;
}

String& String::operator+=(char c)
{
  if (sz == short_max) {
    int n = sz+sz+2;
    ptr = expand(ptr, n);
    space = n-sz-2;
  }
  else if (short_max < sz) {
    if (space == 0) {
      int n = sz+sz+2;
      char* p = expand(ptr, n);
      delete[] ptr;
      ptr = p;
      space = n-sz-2;
    }
    else {
      --space;
    }
  }
  ptr[sz] = c;
  ptr[++sz] = 0;

  return *this;
}


