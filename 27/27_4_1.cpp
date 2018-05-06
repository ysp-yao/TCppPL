template<typename N>
struct Node_base {
  static_assert(Totally_ordered<N>(), "Node_base:N must have a <");

  N* left_child;
  N* right_child;
  Balancing_info bal;

  Node_base();

  void add_left(N* p)
  {
    if (left_child == nullptr)
      left_child = p;
    else {

    }
  }

  void insert(N& n)
  {
    if (n<left_child)
    else
  }
};

template<typename Val>
struct Node::Node_base<Node<Val> > {
  Val v;
  Node(Val vv);
};

using My_node = Node<double>;

void user(const vector<double>& v)
{
  My_node root;
  int i = 0;

  for (auto x : v) {
    auto p = new My_node{x};
    if (i++ % 2)
      root.add_left(p);
    else
      root.add_right(p);
  }
}

/////////////////

template<typename N, typename Balance>
struct Node_base : Balance {
  //static_assert(Totally_ordered<N>(), "Node_base:N must have a <");

  N* left_child;
  N* right_child;
  //Balancing_info bal;

  Node_base();

  void add_left(N* p)
  {
    if (left_child == nullptr)
      left_child = p;
    else {

    }
  }

  void insert(N& n)
  {
    if (this->compare(n, left_child))
    else
  }
};

template<typename Val, typename Balance>
struct Search_node : public Node_base<Search_node<Val, Balance>, Balance>
{
  Val val;
  Search_node(Val v) :val(v) {}
};

struct Red_black_balance {

};


template<typename T>
using Rbnode = Search_node<T, Red_black_balance>;




