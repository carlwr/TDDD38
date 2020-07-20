#include <iostream>

using namespace std;


template <typename  T>
T sum(T (&array)[3])
{
    T result{};
    for (int i{0}; i < 3; ++i)
    {
    result += array[i];
    }
    return result;
}


int main(){
    double x[] = {1.5,2.0,3.0};
    int y[] = {1,2,3};

    cout << sum(x) << "\n";
    cout << sum(y)<< "\n" ;

}