#include <iostream>
#include <sstream>
#include <fstream>
using namespace std;

struct Player
{
    string name;
    double age;
    int height;
};

template <typename T>
void write(ostream& os, T const& t)
{
    os << t << ' ';
}

void write(ostream& os, string const s){
    os << "#" + s + "#";
}

void write (ostream& os, Player const p){
    write(os, p.name);
    write(os, p.age);
    write(os, p.height);
}

int main(){
    ifstream myfile;
    myfile.open("example.txt");
    myfile.clear();
    if(myfile.peek() == EOF){
        cout << "NO file\n";
        string name;
        int age;
        double height;
        cout << "name: ";
        cin >> name;
        cout << "age: ";
        cin >> age;
        cout << "height";
        cin >> height;
        std::ofstream myfile;
        myfile.open("example.txt");
        stringstream ss;
        { // send data to ss
            Player player {name, age, height};
            write(ss, player);
        }
        myfile << ss.rdbuf();
        myfile.close();
    }
    else{
        cout << "file\n";

    }


}