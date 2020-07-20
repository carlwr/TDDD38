#include <istream>
#include <sstream>
#include <iostream>
#include <limits>

using namespace std;

struct Product
{
    string name;
    double price;
    int inventory;
};

ostream& operator<<(ostream& os, Product const& product)
{
    return os << product.name << ": "
              << product.price << " kr ("
              << product.inventory << " available)";
}

template <typename T>
T read(istream& is)
{
    T data;
    is >> data;
    return data;
}

template <>
string read<string>(istream& is)
{
    string str{};
    is.ignore(numeric_limits<streamsize>::max(), '#');
    getline(is, str, '#');
    return str;
}

template <>
Product read<Product>(istream& is)
{
    return {read<string>(is), read<double>(is), read<int>(is)};
}


template <typename T>
void write(ostream& os, T const& t)
{
    os << t << ' ';
}

void write(ostream& os, string const s){
    os << "#" + s + "#";
}

void write (ostream& os, Product const p){
    write(os, p.name);
    write(os, p.price);
    write(os, p.inventory);
}

int main()
{
    stringstream ss;
    { // send data to ss
        Product apple {"Red Apple", 1.5, 100};
        Product laptop{"Laptop", 5995.0, 10};
        Product monitor{"4K Monitor", 8790.0, 1};
        write(ss, apple);
        write(ss, laptop);
        write(ss, monitor);
    }

    { // recieve data from ss
        Product apple  {read<Product>(ss)};
        Product laptop {read<Product>(ss)};
        Product monitor{read<Product>(ss)};
        cout << apple << endl
             << laptop << endl
             << monitor << endl;
    }
}
