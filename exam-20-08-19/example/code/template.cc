#include <iostream>
#include <type_traits>
#include <string>

namespace spec{

    std::string hej(int a, int){

        return "2";
    }

    template<typename T>
    std::string hej(T a, float){

        return "1";
    }

}

template<typename T>
std::string hej(T a){
    return spec::hej(a, 1.0);
}

int main(){
    std::cout << "test: ";
    std::cout << hej(1) << std::endl;
}