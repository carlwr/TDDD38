#include "Node.h"

/*
  Implement the functionality of the Node hierarchy
 */
using namespace std;

Number::Number(double value)
    : value{value}
{
}

double Number::evaluate() const {
  return value;
}

void Number::print_tree(ostream & os, int intendents = 0) const{
    os << setw(intendents);
    os << value << endl;
  
}

Node* Number::clone() const {
  return new Number{value};
}


Operator::Operator(Node* left, Node* right) : left{left}, right{right}{}
Operator::~Operator(){delete left; delete right;}

double Operator::evaluate() const {

}


void Operator::print_tree(ostream & os, int intendents = 0) const{

}

Node* Operator::clone() const {

}


double Addition::evaluate() const {
  return left->evaluate() + right->evaluate();
}

void Addition::print_tree(ostream & os, int intendents = 0) const{
    right->print_tree(os, intendents + 2);
    os << setw(intendents + 1);
    os << "/" << endl;

    os << setw(intendents);
    os << "+" << endl;

    os << setw(intendents + 1);
    os << "\\" << endl;

    left->print_tree(os, intendents + 2);

}

Node* Addition::clone() const {
  return new Addition{left, right};
}


double Subtraction::evaluate() const {
  return left->evaluate() - right->evaluate();

}


void Subtraction::print_tree(ostream & os, int intendents = 0) const{
  right->print_tree(os, intendents + 2);
    
    os << setw(intendents + 1);
    os << "/" << endl;

    os << setw(intendents);
    os << "-" << endl;

    os << setw(intendents + 1);
    os << "\\" << endl;

    left->print_tree(os, intendents + 2);


}

Node* Subtraction::clone() const {
  return new Subtraction{left, right};

}


double Multiplication::evaluate() const {
  return left->evaluate() * right->evaluate();

}


void Multiplication::print_tree(ostream & os, int intendents = 0) const{
  right->print_tree(os, intendents + 2);
    
    os << setw(intendents + 1);
    os << "/" << endl;

    os << setw(intendents);
    os << "*" << endl;

    os << setw(intendents + 1);
    os << "\\" << endl;

    left->print_tree(os, intendents + 2);


}

Node* Multiplication::clone() const {
  return new Multiplication{left, right};

}


double Division::evaluate() const {
  return left->evaluate() / right->evaluate();

}


void Division::print_tree(ostream & os, int intendents = 0) const{
  right->print_tree(os, intendents + 2);
    
    os << setw(intendents + 1);
    os << "/" << endl;

    os << setw(intendents);
    os << "/" << endl;

    os << setw(intendents + 1);
    os << "\\" << endl;

    left->print_tree(os, intendents + 2);


}

Node* Division::clone() const {
  return new Division{left, right};

}