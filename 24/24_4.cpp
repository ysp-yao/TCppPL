//template<typename T>
//constexpr bool Semiregular()
//{
//  return Destructible<T>()
//    && Default_constructible<T>()
//    && Move_constructible<T>()
//    && Move_assignable<T>()
//    && Copy_constructible<T>()
//    && Copy_assignable<T>();
//}
//
//template<typename T>
//constexpr bool Equality_comparable()
//{
//  return Has_equality<T>() && Boolean<Equal_result<T>>() // ==
//    && Has_not_equality<T>() && Boolean<Not_equal_result<T>>(); // !=
//}
//
//template<typename T>
//constexpr bool Regular()
//{
//  return Semiregular<T>() && Equality_comparable<T>();
//}
//
//template<typename T>
//constexpr bool Totally_ordered()
//{
//  return Equality_comparable<T>() //  ==,!=
//    && Has_less<T>() && Boolean<Less_result<T>>() //  <
//    && Has_greater<T>() && Boolean<Greater_result<T>>() //  >
//    && Has_less_equal<T>() && Boolean<Less_equal_result<T>>() //  <=
//    && Has_greater_equal<T>() && Boolean<Greater_equal_result<T>>();  //  >=
//}
//
//template<typename T>
//constexpr bool Ordered()
//{
//  return Regular<T>() && Totally_ordered<T>();
//}
//
//template<typename T>
//constexpr bool Streamable()
//{
//  return Input_streamable<T>() && Output_streamable<T>();
//}