#include <iostream>

class Joakim{
public:
    Joakim(int x) : x{new int{x}}{
        std::cout << "default" << std::endl;
    }
    ~Joakim(){
        std::cout << "delete" << std::endl;

        delete x;
    }
    Joakim(Joakim const& other): Joakim{*other.x}{
        std::cout << "copy constructor" << std::endl;

    }   

    Joakim(Joakim&& other){
        std::cout << "move constructor" << std::endl;

    }

    Joakim& operator=(Joakim const& other){
        std::cout << "copy assignment" << std::endl;

        *x = *other.x;
    };
    int* x;
};


int main(){
    // Joakim a{2};
    // Joakim Wallentin = a;
    // std::cout << *Wallentin.x << std::endl;

    // *a.x = 3;
    // std::cout << *Wallentin.x << std::endl;


}