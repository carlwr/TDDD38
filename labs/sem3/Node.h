/*
  Implement the classes:
  - Node
  - Number
  - Operator
  - Addition
  - Subtraction
  - Multiplication
  - Division

  Node should have the following (pure virtual) members:
  - double evaluate()
    + Calculate the expression stored in 'this'
  - void print(std::ostream& os)
    + print the expression represented in 'this'
  - void print_tree(std::ostream& os, int depth)
    + print a textual representation of the expression tree
  - Node* clone()
    + return a a new instance of the expression stored in 'this'
 */
#include <iostream>
#include <iomanip>
using namespace std;


class Node{
  public:
    virtual ~Node() = default;

    virtual double evaluate() const = 0;
    virtual void print_tree(ostream&, int) const = 0;
    virtual Node* clone() const = 0;
  private:
};


class Number : public Node{
  public:
    Number(double value);
    double evaluate() const override;
    void print_tree(ostream&, int) const override;
    Node* clone() const  override;
  private:
    double value;

};


class Operator : public Node{
  public:
    Operator(Node* left, Node* right);
    ~Operator();
    double evaluate() const  override;
    void print_tree(ostream&, int) const override;
    Node* clone() const  override;
  protected:
    Node* left;
    Node* right;
};

class Addition :public Operator{
  public:
    using Operator::Operator;
    double evaluate() const  override;
    void print_tree(ostream&, int) const override;
    Node* clone() const  override;
};

class Subtraction : public Addition{
  public:
    using Addition::Addition;
    double evaluate() const  override;
    void print_tree(ostream&, int) const override;
    Node* clone() const  override;
};


class Multiplication : public Operator{
  public:
    using Operator::Operator;
    double evaluate() const  override;
    void print_tree(ostream&, int) const override;
    Node* clone() const  override;
};

class Division : public Multiplication{
  public:
    using Multiplication::Multiplication;
    double evaluate() const  override;
    void print_tree(ostream&, int) const override;
    Node* clone() const  override;
};