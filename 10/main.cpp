#include <iostream>
#include <cctype>

enum class Kind : char {
  name, number, end,
  plus='+', minus='-', mul='*', div='/', print=';', assign='=', lp='(', rp=')'
};

struct Token {
  Kind kind;
  std::string string_value;
  double number_value;
};

class Token_stream {
public:
  Token get();
  const Token& current();
};

double expr(bool get) // 加法和减法
{
  double left = term(get);

  for (;;) {
    switch (ts.current().kind) {
    case Kind::plus:
      left += term(true);
      break;
    case Kind::minus:
      left -= term(true);
      break;
    default:
      return left;
    }
  }
}

double term(bool get) // 乘法和除法
{
  double left = prim(get);

  for (;;) {
    switch (ts.current().kind) {
    case Kind::mul:
      left *= prim(true);
      break;
    case Kind::div:
      if (auto d = prim(true)) {
        left /= d;
        break;
      }
      return error("divide by 0");
    default:
      return left;
    }
  }
}

double prim(bool get)
{
  if (get) ts.get();

  switch (ts.current().kind) {
  case Kind::number:
  {
    double v = ts.current().number_value;
    ts.get();
    return v;
  }
  case Kind::name:
  {
    double& v = table[ts.current().string_value];
    if (ts.get().kind == Kind::assign) v = expr(true);
    return v;
  }
  case Kind::minus:
    return -prim(true);
  case Kind::lp:
  {
    auto e = expr(true);
    if (ts.current().kind != Kind::rp) return error("')'expected");
    ts.get();
    return e;
  }
  default:
    return error("primary expected");
  }
}

class Token_stream {
public:
  Token_stream(std::istream& s) :ip{&s}, owns{ false } {}
  Token_stream(std::istream* p) :ip{ p }, owns{ false } {}

  ~Token_stream(){ close(); }

  Token get();        //  读取并返回下一个单词
  Token& current();   //  刚刚输入的单词

  void set_input(std::istream& s) { close(); ip = &s; owns = false; }
  void set_input(std::istream* p) { close(); ip = p; owns = false; }

private:
  void close() { if (owns) delete ip; }

  std::istream* ip;
  bool owns;            
  Token ct{Kind::end};  // 当前单词
};

Token Token_stream::get()
{
  char ch = 0;
  *ip >> ch;

  switch (ch) {
  case 0:
    return ct = {Kind::end};
  case ';':
  case '*':
  case '/':
  case '+':
  case '-':
  case '(':
  case ')':
  case '=':
    return ct = {static_cast<Kind>(ch)};
  case '0':case '1':case '2':case '3':case '4':case '5':case '6':case '7':case '8':case '9':
  case '.':
    ip->putback(ch);
    *ip >> ct.number_value;
    ct.kind = Kind::number;
    return ct;
  default:
    if (std::isalpha(ch)) {
      ip->putback(ch);
      *ip >> ct.string_value;
      ct.kind = Kind::name;
      return ct;
    }
    error("bad token");
    return ct = { Kind::print };
  }
}

int no_of_errors;

double error(const std::string& s)
{
  no_of_errors++;
  std::cerr << "error:" << s << '\n';
  return 1;
}