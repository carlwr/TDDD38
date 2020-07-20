#include <cassert>

// implement the Fibonacci class here

int main()
{
  assert(Fibonacci<0>::value == 0);
  assert(Fibonacci<1>::value == 1);
  assert(Fibonacci<5>::value == 5);
  assert(Fibonacci<10>::value == 55);
  assert(Fibonacci<12>::value == 144);
}
