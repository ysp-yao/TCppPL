#include <string>
#include <iostream>

template<typename T>
struct Link {
  Link* pre;
  //Link* suc //  error, ����ʵ�������ɼ���
  Link* suc;
  T val;
};

template<typename T>
class List {
  Link<T>* head;
public:
  //List() :head{ 7 } {}  //error, ��Ҫʵ�������ܼ���
  List() :head{ nullptr } {}
  //List(const T& t) :head{ new Link<T> {0,o,t} } {} // error, ����ʵ�������ɼ���
  List(const T& t) :head{ new Link<T>{ 0,0,t } } {}

  void print_all() const;
};

template<typename T>
void List<T>::print_all() const
{
  for (Link<T>* p = head; p; p = p->suc)
    //std::cout << *p;
    std::cout << p->val;
}

class Rec {
  std::string name;
  std::string address;
};

void f(const List<int>& li, const List<Rec>& lr)
{
  li.print_all();
  //lr.print_all(); // error
}

int main() {

  List<int> li;
  List<Rec> lr;
  f(li, lr);
}