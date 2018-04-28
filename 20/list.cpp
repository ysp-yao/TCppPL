#include "list.h"

template<class T>
void List<T>::insert(T val)
{
  Link* lnk = get_free();
  lnk->val = val;
  lnk->next = head;
  head = lnk;
}

template<class T>
T List<T>::get()
{
  if (head==0) throw Underflow{};

  Link* p = head;
  head = p->next;
  p->next = free;
  free = p;
  return p->val;
}

template<class T>
typename List<T>::Link* List<T>::get_free()
//auto List<T>::get_free() -> Link*
{
  if (free==0) {

  }
  Link* p = free;
  free = free->next;
  return p;
}