#include <ostream>
#include <iterator>
#include <utility>
#include <iostream>
#include <vector>
#include <map>
#include <tuple>
#include <array>
#include <string>

/* This should give the following output (or something similar at least):
5
{1, 2, 3}
{(1 1), (2 2), (3 3)}
(5 3.14)
{hello, world}
{{ab, c}, {def, g, hi}}
SFINAE
string literal
 */
template<typename T>
void print(std::ostream& os, T const& data);


namespace spec{
  template<typename T>
  void printContainer(std::ostream& os, T const& data){
    os << "{";
    ::print(os, data[0]);
  }

  void print(std::ostream& os, char const* data, int){
    os << data;
  }

  void print(std::ostream& os, std::string const&  data, int){
    os << "string";
  }
  
  template<typename T, size_t N>
  void printContainer(std::ostream& os, T const& data){
    os << "{";
    while(begin(data) != end(data)){
      ::print(os, );
    }
  }

  void print(std::ostream& os, std::array<T, N> const& data, int){
    printContainer(os, data);
  }

  template<typename T>
  auto print(std::ostream& os, T const& data, int)
  -> decltype(std::begin(data), std::declval<void>())
  {
    os << "container";
  }

  template<typename T>
  auto print(std::ostream& os, T const& data, int)
  -> decltype(std::tuple_size<T>(), std::declval<void>())
  {
    os << "Tuple";
  }


  //last
  template<typename T>
  void print(std::ostream& os, T const& data, float){
    os << data;
  }

}

template<typename T>
void print(std::ostream& os, T const& data){
 spec::print(os, data, 0);

}


int main()
{
  print(std::cout, 5);
  std::cout << std::endl;
  
  std::vector<int> v {1, 2, 3};
  print(std::cout, v);
  std::cout << std::endl;

  std::map<int, int> m { {1, 1}, {2, 2}, {3, 3} };
  print(std::cout, m);
  std::cout << std::endl;

  std::tuple<int, double> t { 5, 3.14 };
  print(std::cout, t);
  std::cout << std::endl;

  std::string s[] { "hello", "world" };
  print(std::cout, s);
  std::cout << std::endl;
  
  std::array<std::vector<std::string>, 2> a {
    std::vector<std::string>{ "ab", "c" },
    std::vector<std::string>{"def", "g", "hi"}
  };
  
  print(std::cout, a);
  std::cout << std::endl;

  char const* str {"SFINAE"};
  print(std::cout, str);
  std::cout << std::endl;

  print(std::cout, "string literal");
  std::cout << std::endl;
}
