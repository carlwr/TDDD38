#ifndef PRINTER_H_
#define PRINTER_H_

#include <iostream>

/* version 1 */

// this namespace is inlined so that
// we easily can switch between version_1
// and version_2
inline namespace version_1
{
namespace detail
{
    // base case
    void print_helper()
    {
      std::cout << std::endl;
    }
    
    template <typename Arg, typename... Args>
    void print_helper(Arg first, Args... rest)
    {
      std::cout << first << ' ';
      print_helper(rest...);
    }
}
template <typename... Args>
void print(Args... args)
{
  detail::print_helper(args...);
}
}

/* version 2: C++17 */

namespace version_2
{
template <typename... Args>
void print(Args... args)
{
  /*
    C++17
    Fold expressions can expand using any operator including the comma-operator

    Assume that we call:
    print(1, 2, 3)

    Then this fold will expand to:

    (cout << 1 << " "), (cout << 2 << " "), (cout << 3 << " ")

    which is equivalent to:

    cout << 1 << " ";
    cout << 2 << " ";
    cout << 3 << " ";
  */
  ((std::cout << args << " "), ...);
  std::cout << std::endl;
}
}

#endif//PRINTER_H_
