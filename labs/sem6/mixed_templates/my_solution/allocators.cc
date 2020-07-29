#include <cassert>
#include <iostream>

template <typename T>
struct New_Allocator{
   static New_Allocator<T>* create(Ts... ts){
    return new New_Allocator<T>(ts);
  }
  static void destroy(New_Allocator<T>* ta){
    delete ta;
  }
};


template <typename T>
struct Tracker_Allocator{
  static Tracker_Allocator<T>* create(Ts... ts){
    std::cout << "created ta" << std::endl;
    return new Tracker_Allocator<T>(ts);
  }
  static void destroy(Tracker_Allocator<T>* ta){
    std::cout << "destroyed ta" << std::endl;
    delete ta;
  }
  
};

template <typename T, typename Allocator = New_Allocator<T>>
class Stack
{

  struct Node;
  
public:

  Stack()
    : head{nullptr} { }

  Stack(Stack const&) = delete;
  Stack(Stack&&) = delete;

  Stack& operator=(Stack const&) = delete;
  Stack& operator=(Stack&&) = delete;
  
  ~Stack()
  {
    while (!empty())
    {
      pop();
    }
  }
  
  void push(int const& value)
  {
    head = new Node{value, head};
  }

  int pop()
  {
    int result{top()};
    Node* old {head};
    head = head->next;
    delete old;
    return result;
  }

  int& top()
  {
    return head->value;
  }

  int const& top() const
  {
    return head->value;
  }

  bool empty() const
  {
    return head == nullptr;
  }
  
private:
  
  struct Node
  {
    int value;
    Node* next;
  };

  Node* head;
  
};

int main()
{
  Stack st {};
  assert(st.empty());
  
  st.push(1);
  assert(!st.empty());
  assert(st.top() == 1);
  
  st.push(2);
  assert(st.top() == 2);
  assert(st.pop() == 2);
  
  assert(st.pop() == 1);

  assert(st.empty());

  st.push(3);
  assert(st.pop() == 3);
  
  st.push(4);
  
  st.push(5);
  assert(st.pop() == 5);
}
