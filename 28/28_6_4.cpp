template<typename Head, typename... Tail>
class tuple<Head, Tail...>
  :private tuple<Tail...> {

  typedef tuple<Tail...> inherited;
public:
  constexpr tuple() {}
  
  tuple(Add_const_reference<Head> v, Add_const_reference<Tail>... vtail)
    :m_head(v), inherited(vtail...) {}

  template<typename... VValues>
  tuple(const tuple<VValue...>& other)
    : m_head(other.head()), inherited(other.tail) {}

  template<typename... VValues>
  tuple& operator=(const tuple<VValues...>& other)
  {
    m_head = other.head();
    tail() = other.tail();
    return *this;
  }

protected:
  Head m_head;
private:
  Add_reference<Head> head() { return m_head; }
  Add_const_reference<const Head> head() const { return m_head; }

  inherited& tail() { return *this; }
  const inherited& tail const{ return *this; }
};