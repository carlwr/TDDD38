template <typename T, int chunk_size>
deque<T, chunk_size>::deque()
    : data       {new T*[1]{}},
      capacity   {1},
      chunk_count{0},
      count      {0},
      start      {0}
{ }

template <typename T, int chunk_size>
deque<T, chunk_size>::deque(deque<T, chunk_size> const& other)
    : deque{}
{
    for (int i{0}; i < other.size(); ++i)
    {
        push_back(other[i]);
    }
}

template <typename T, int chunk_size>
deque<T, chunk_size>::deque(deque<T, chunk_size>&& other)
    : deque{}
{
    *this = std::move(other);
}

template <typename T, int chunk_size>
deque<T, chunk_size>::~deque()
{
    // delete all the allocated chunks
    for (int i{0}; i < chunk_count; ++i)
    {
        delete[] data[i];
    }
    delete[] data;
}

template <typename T, int chunk_size>
deque<T, chunk_size>& deque<T, chunk_size>::operator=(deque<T, chunk_size> const& other)
{
    return *this = std::move(deque{other});
}

template <typename T, int chunk_size>
deque<T, chunk_size>& deque<T, chunk_size>::operator=(deque<T, chunk_size>&& other)
{
    std::swap(data, other.data);
    std::swap(capacity, other.capacity);
    std::swap(chunk_count, other.chunk_count);
    std::swap(count, other.count);
    std::swap(start, other.start);
    return *this;
}

template <typename T, int chunk_size>
void deque<T, chunk_size>::push_back(T const& value)
{
    int next_chunk {(count + start) / chunk_size};
    int next_index {(count + start) % chunk_size};
    if (next_index == 0)
    {
        add_chunk_back();
    }
    data[next_chunk][next_index] = value;
    ++count;
}

template <typename T, int chunk_size>
void deque<T, chunk_size>::push_front(T const& value)
{
    if (start > 0)
    {
        --start;            
    }
    else
    {
        add_chunk_front();
        start = chunk_size - 1;
    }
    data[0][start] = value;
    ++count;
}

template <typename T, int chunk_size>
void deque<T, chunk_size>::pop_front()
{
    if (count > 0)
    {
        ++start;
        remove_chunk_front();
        --count;
    }
    else
    {
        throw std::out_of_range{"Cannot pop empty deque!"};
    }
}

template <typename T, int chunk_size>
void deque<T, chunk_size>::pop_back()
{
    if (count > 0)
    {
        remove_chunk_back();
        --count;
    }
    else
    {
        throw std::out_of_range{"Cannot pop empty deque!"};
    }
}

template <typename T, int chunk_size>
T& deque<T, chunk_size>::operator[](int i)
{
    // reuse code by 
    return const_cast<T&>(static_cast<deque const*>(this)->operator[](i));
}

template <typename T, int chunk_size>
T const& deque<T, chunk_size>::operator[](int i) const
{
    int chunk{(i + start) / chunk_size};
    int index{(i + start) % chunk_size};
    return data[chunk][index];
}

template <typename T, int chunk_size>
T& deque<T, chunk_size>::at(int i)
{
    return const_cast<T&>(static_cast<deque const*>(this)->at(i));
}

template <typename T, int chunk_size>
T const& deque<T, chunk_size>::at(int i) const
{
    if (i < 0 || i >= count)
        throw std::out_of_range{"deque out of range"};
    return operator[](i);
}

template <typename T, int chunk_size>
int deque<T, chunk_size>::size() const
{
    return count;
}

template <typename T, int chunk_size>
void deque<T, chunk_size>::remove_chunk_back()
{
    int chunk{(count + start - 1) / chunk_size};
    int index{(count + start - 1) % chunk_size};
    if (index == 0)
    {
        --chunk_count;
        delete[] data[chunk];
    }
}
template <typename T, int chunk_size>
void deque<T, chunk_size>::remove_chunk_front()
{
    if (start >= chunk_size)
    {
        start = 0;
        delete[] data[0];
        std::move_backward(data + 1, data + chunk_count,
                           data + chunk_count - 1);
        --chunk_count;
    }
}

template <typename T, int chunk_size>
void deque<T, chunk_size>::add_chunk_back()
{
    reallocate_chunk_array();
    data[chunk_count++] = new T[chunk_size]{};
}

template <typename T, int chunk_size>
void deque<T, chunk_size>::add_chunk_front()
{
    reallocate_chunk_array();

    // move every chunk pointer up one slot to make room for the new
    // chunk at the front of the deque.
    std::move(data, data + chunk_count, data + 1);
    
    data[0] = new T[chunk_size]{};
    ++chunk_count;
}

template <typename T, int chunk_size>
void deque<T, chunk_size>::reallocate_chunk_array()
{
    if (chunk_count >= capacity)
    {
        capacity *= 2;
        T** new_array {new T*[capacity]{}};
        
        std::copy(data, data + chunk_count, new_array);
        
        delete[] data;
        data = new_array;
    }
}
