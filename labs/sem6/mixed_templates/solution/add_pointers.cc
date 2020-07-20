#include <type_traits>

namespace details
{
    template <typename T, typename U, typename = std::enable_if_t<!std::is_pointer_v<U>>>
    T add_pointers_helper();

    /*
      auto add_pointers() -> decltype(details::add_pointers<T*, std::remove_pointer_t<U>>());

      Won't work. The trailing return type is a decltype, so (because
      of expression SFINAE) this will force the compiler to check that
      the expression inside decltype(...) is checked for validity
      during overload resolution of add_pointers. During these checks
      the compiler is not allowed to instantiate templates.

      And, as we can see, the decltype must check what the resulting
      return type is of add_pointer<T*, std::remove_pointer_t<U>> but
      in order to do so the compiler must first instantiate the
      function for these new template parameters, which is not
      allowed, thus giving us a compile error.

      In C++14 auto as return type was added. This gives us a way to
      fix this:

      The fix is to instead let the compiler deduce the return type
      during instantiation, which happens after overload resolution.

      This is done by declaring the return type as auto (without a
      trailing return type), and then implementing the function with
      the correct return statement. Since the body of the function
      does not matter during overload resolution the compiler cannot
      yet deduce the return type when it is declared as auto. This
      means that the compiler has to wait until it actually
      instantiates the function template before it can decide.
    */
    template <typename T, typename U, typename = std::enable_if_t<std::is_pointer_v<U>>>
    auto add_pointers_helper()
    {
      return details::add_pointers<T*, std::remove_pointer_t<U>>();
    }
}

template <typename T, typename U>
struct add_pointers
{
  using type = decltype(details::add_pointers<T, U>());
};

int main()
{
  static_assert(std::is_same_v<add_pointers<int, int>::type, int>, "int + int = int");
  static_assert(std::is_same_v<add_pointers<int, int*>::type, int*>, "int + int* = int*");
  static_assert(std::is_same_v<add_pointers<int*, int*>::type, int**>, "int* + int* = int**");
  static_assert(std::is_same_v<add_pointers<int**, int*>::type, int***>, "int** + int* = int**");
  static_assert(std::is_same_v<add_pointers<int**, int***>::type, int*****>, "int** + int*** = int*****");
}
