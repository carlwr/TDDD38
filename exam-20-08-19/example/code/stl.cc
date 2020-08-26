#include <algorithm>
#include <iterator>
#include <iostream>
#include <string>
#include <fstream>

//containers
#include <vector>
#include <deque>
#include <list>

int main(){

    std::vector<int> a {};
    std::copy(std::istream_iterator<int>(std::cin), 
    std::istream_iterator<int>(),std::back_inserter(a));
    std::vector<int> b {a};
    
    std::transform(std::begin(b), std::end(b), std::begin(a), [](int& u){
        return ++u;
    });
    std::cout << "a: ";
    std::copy(std::begin(a), std::end(a), std::ostream_iterator<int>(std::cout, " "));


    std::cout << "None is bigger than 0: " << std::none_of(std::begin(a), std::end(a), [](int const& i){ return i > 0;}) << std::endl;

    std::vector<std::string> words{};
    std::ifstream ifs("SY");
    std::copy(std::istream_iterator<std::string>{ifs}, std::istream_iterator<std::string>{}, std::back_inserter(words));
    std::copy(std::begin(words), std::end(words), std::ostream_iterator<std::string>(std::cout, " "));


}