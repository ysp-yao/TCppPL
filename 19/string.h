#ifndef zzzzSTRING_H_
#define zzzzSTRING_H_

#include <stdexcept>
#include <cstring>
#include <iostream>
#include <istream>

class String {
public:
  // 19.3.1 必备操作
  String();

//  explicit String(const char* p);
  String(const char* p);


  String(const String&);
  String& operator=(const String&);
  String(String&& x);
  String& operator=(String&& x);

  ~String(){if(short_max<sz) delete[] ptr;}

  // 访问字符
  char& operator[](int n){return ptr[n];}
  char operator[](int n)const{return ptr[n];}
  
  char& at(int n){check(n);return ptr[n];}
  char at(int n)const{check(n);return ptr[n];}

  String& operator+=(char c);

  const char* c_str() {return ptr;}
  const char* c_str() const {return ptr;}

  int size() const {return sz;}
  int capacity() const 
    {return (sz<=short_max)?short_max:sz+space;}

private:
  static const int short_max = 15;
  //int sz;
  size_t sz;
  char* ptr;
  union {
    int space;
    char ch[short_max+1];
  };

  void check(int n) const
  {
    if (n<0 || sz<=n)
      throw std::out_of_range("String::at()");
  }
  
  void copy_from(const String& x);
  void move_from(String& x);
};

inline char* expand(const char* ptr, int n) {
  char* p = new char[n];
  strcpy(p, ptr);
  return p;
}

inline std::ostream& operator<<(std::ostream& os, const String& s)
{
  return os<<s.c_str();
}

inline std::istream& operator>>(std::istream& is, String& s)
{
  s = "";
  is >> std::ws;
  char ch = ' ';
  while(is.get(ch)&&!isspace(ch))
    s += ch;
  return is;
}

inline bool operator==(const String& a, const String& b)
{
  if (a.size() != b.size())
    return false;
  for (int i=0; i!=a.size(); ++i)
    if (a[i]!=b[i])
      return false;
  return true;
}

inline bool operator!=(const String& a, const String& b)
{
  return !(a==b);
}

inline char* begin(String& x)
{
  return const_cast<char*>(x.c_str());
}

inline char* end(String& x)
{
  return const_cast<char*>(x.c_str()+x.size());
}

inline const char* begin(const String& x)
{
  return x.c_str();
}

inline const char* end(const String& x)
{
  return x.c_str()+x.size();
}

inline String& operator+=(String& a, const String& b)
{
  for (auto x:b)
    a+=x;
  return a;
}

inline String operator+(const String& a, const String& b)
{
  String res{a};
  res += b;
  return res;
}

// String operator""_s(const char* p, size_t)
// {
//   return String{p};
// }



#endif // STRING_H_