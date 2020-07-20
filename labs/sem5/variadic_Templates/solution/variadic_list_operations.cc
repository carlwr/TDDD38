#include <iostream>
#include <type_traits>

template <typename... Ts>
struct Pack
{ };

/* Here we use inline namespaces to determine which version of the
 * exercise we want to use. To test version 1, simply put the keyword
 * inline before namespace, i.e.:
 * inline namespace version_1
 *
 * To test version 2, remove the inline keyword from version_1 and add
 * it to version_2 instead.
 */

/* Version 1
   Using recursive template functions */

inline namespace version_1
{

namespace detail
{
    template <typename T, typename First, typename... Rest>
    bool contains(Pack<First, Rest...>)
    {
      Pack<Rest...> rest;
      return std::is_same_v<T, First> || contains<T>(rest);
    }

    template <typename T>
    bool contains(Pack<>)
    {
      return false;
    }

    template <typename T>
    int index_of(Pack<>, int index)
    {
      return -1;
    }
    
    template <typename T, typename First, typename... Rest>
    int index_of(Pack<First, Rest...>, int index)
    {
      if (std::is_same_v<T, First>)
      {
        return index;
      }
      Pack<Rest...> rest;
      return index_of<T>(rest, index + 1);
    }
}

template <typename T, typename... Ts>
bool contains(Pack<Ts...> p)
{
  return detail::contains<T>(p);
}

template <typename T, typename... Ts>
int index_of(Pack<Ts...> p)
{
  return detail::index_of<T>(p, 0);
}

}

/* Version 2
   Using fold expressions */

namespace version_2
{

template <typename T, typename... Ts>
bool contains(Pack<Ts...> p)
{
  return (std::is_same_v<T, Ts> || ...);
}

/*
  Let's build this solution from the ground up:

  We know from 'contains' how to check if an element
  exists:

  (std::is_same_v<T, Ts> || ...)

  This will return 'true' if T is present in Ts

  We can use the comma-operator to evaluate multiple
  expressions in this fold-expression, for example:

  ((std::cout << "hello", std::is_same_v<T, Ts>) || ...)

  If we run this expression we can note that this will print "hello"
  for each element before the one we searched for and then one more
  time. That means that these expressions don't evaluate for each
  element in the pack, but instead it only evaluates the once
  neccessary to determine if the ||-expression is true.

  Since a || b is guaranteed to be true if a is true, there is no need
  to check the value of b, so the evaulation will stop prematurely and
  never evaluate b.

  We can leverage this behaviour to count how many elements where checked
  before the existence of T was 100% determined. We do this like so:

  int count{0};
  ((++count, std::is_same_v<T, Ts>) || ...)

  This will determine what index T has in the pack if we just subtract
  1 from the variable 'count'. So we can modify it as such:

  int index{-1};
  ((++index, std::is_same_v<T, Ts>) || ...)

  Now we have the index, but if T is not present in Ts we will get a
  faulty index. In this case we want to always return -1 if T was not
  found in Ts. How do we check if T is present?

  Well, that is determined by the return value of the fold-expression,
  since it is based on the contains function, so if the element was
  found the fold-expression will return true, otherwise it will return
  false, so if the expresssion returns false, we should return -1
  and index otherwise.
 */
template <typename T, typename... Ts>
int index_of(Pack<Ts...> p)
{
  int index{-1};
  if (((++index, std::is_same_v<T, Ts>) || ...))
    return index;
  return -1;
}

}
    
int main()
{
  using std::cout;
  using std::endl;
  Pack<int, double, long, float, std::string> p{};

  cout << contains<long>(p) << endl;
  cout << contains<char>(p) << endl;
  cout << endl;
  cout << index_of<int>(p) << endl;
  cout << index_of<float>(p) << endl;
  cout << index_of<char>(p) << endl;
}
