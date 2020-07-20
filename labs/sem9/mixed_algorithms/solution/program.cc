#include <vector>
#include <algorithm>
#include <numeric>
#include <iostream>
#include <iterator>

using namespace std;

int main()
{
    int N;
    cout << "How many? ";
    cin >> N;
    vector<unsigned long long int> fib (N, 1);
    adjacent_difference(begin(fib), end(fib), next(begin(fib)), plus<unsigned long long int>{});
    copy(begin(fib), end(fib), ostream_iterator<unsigned long long int>{cout, "\n"});
}
