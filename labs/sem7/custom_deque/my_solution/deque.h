


template<typename T, typename chunk_size>
class deque{
public:
    
    deque();
    deque(deque const& other);
    deque(deque&& other);
    ~deque();

    deque& operator=(deque const& other);
    deque& operator=(deque&& other);

    void push_front(T const& value);
    void push_back(T const& value);

    void pop_front();
    void pop_back();

    T& operator[](int ind);
    T const& operator[](int ind) const;
    
    T& at(int i);
    T const& at(int i) const;
private:
};