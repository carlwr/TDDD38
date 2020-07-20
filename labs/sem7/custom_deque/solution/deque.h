#ifndef DEQUE_H_
#define DEQUE_H_

#include <stdexcept>
#include <utility>

template <typename T, int chunk_size = 128>
class deque
{

public:

    deque();
    deque(deque const& other);
    deque(deque&& other);
    ~deque();

    deque& operator=(deque const& other);
    deque& operator=(deque&& other);
    
    void push_back (T const& value);
    void push_front(T const& value);

    void pop_front();
    void pop_back ();
    
    T&       operator[](int i);
    T const& operator[](int i) const;
    
    T&       at(int i);
    T const& at(int i) const;

    int size() const;
    
private:

    void remove_chunk_back();
    void remove_chunk_front();
    
    void add_chunk_back();
    void add_chunk_front();
    void reallocate_chunk_array();
    
    T** data;
    int capacity;
    int chunk_count;
    int count;
    int start;
    
};

#include "deque.tcc"
#endif//DEQUE_H_
