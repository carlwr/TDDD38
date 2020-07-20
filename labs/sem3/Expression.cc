#include "Expression.h"

#include <stdexcept>
#include <ostream>

/* Implement Expression here */

/* For part B */
void Expression::print(std::ostream& os) const
{
    throw std::invalid_argument{"--print is unimplemented"};
}

/* For part C */
void Expression::expand()
{
    throw std::invalid_argument{"--expand is unimplemented"};
}


void Expression::print_tree(std::ostream& os) const{

    root->print_tree(os, 0);
}

double Expression::evaluate() const{
    return root->evaluate();
}

Expression::~Expression(){
    delete root;
}

Expression::Expression(Node* root): root{root}{}

