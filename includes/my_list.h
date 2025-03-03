#include <concepts>
#include <cstddef>
#include <initializer_list>
#include <iterator>
#include <memory>




template<typename T> class MyList
{
    struct Node;

public:
    using value_type = T;
    using size_type = size_t;
    using difference_type = ptrdiff_t;
    using pointer = value_type*;
    using const_pointer = const value_type*;
    using reference = value_type&;
    using const_reference = const value_type&;

    class iterator
    {
    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = value_type;
        using difference_type = difference_type;
        using pointer = pointer;
        using reference = reference;

        iterator(Node* n) : _n{n} {}

        bool operator==(const iterator& other) const;
        bool operator!=(const iterator& other) const;
        pointer operator->();
        iterator& operator--();
        iterator operator--(int);
        iterator& operator++();
        iterator operator++(int);
        reference operator*();

        Node* current() { return _n; }
        friend class MyList;

    private:
        Node* _n;
    };



    using reverse_iterator = std::reverse_iterator<iterator>;

    MyList();
    MyList(MyList& other);
    MyList(std::initializer_list<T> init);

    MyList& operator=(MyList& other);
    MyList& operator=(std::initializer_list<T> ilist);

    reference front();
    reference back();

    iterator begin() noexcept;
    iterator end() noexcept;

    reverse_iterator rbegin() noexcept;
    reverse_iterator rend() noexcept;

    bool empty() const noexcept;
    size_type size() const noexcept;

    void clear() noexcept;

    iterator insert(iterator pos, const T& value);

    iterator erase(iterator pos);
    iterator erase(iterator first, iterator last);

    void push_back(const T& value);
    void pop_back();
    void push_front(const T& value);
    void pop_front();

    void reverse() noexcept;
    void swap(MyList& other) noexcept;

    std::size_t count_positive();
    value_type find_max();
    std::size_t count_max_elems();
    std::pair<MyList, MyList> split();

    ~MyList();

private:
    struct Node
    {
        Node(value_type d, Node* p = nullptr, Node* n = nullptr)
            : data{d}, prev{p}, next{n}
        {
        }

        value_type data;
        Node* prev;
        Node* next;
    };

    Node* _tail;
    Node* _head;
    std::size_t _size;
};


// TODO: добавить методы из условия лабы


template<class T>
bool MyList<T>::iterator::operator==(const iterator& other) const
{
    return _n == other._n;
}

template<class T>
bool MyList<T>::iterator::operator!=(const iterator& other) const
{
    return !(*this == other);
}

template<class T> MyList<T>::pointer MyList<T>::iterator::operator->()
{
    return _n;
}

template<class T> MyList<T>::iterator& MyList<T>::iterator::operator--()
{
    _n = _n->prev;

    return *this;
}

template<class T> MyList<T>::iterator MyList<T>::iterator::operator--(int)
{
    auto temp{*this};
    _n = _n->prev;

    return temp;
}

template<class T> MyList<T>::iterator& MyList<T>::iterator::operator++()
{
    _n = _n->next;

    return *this;
}

template<class T> MyList<T>::iterator MyList<T>::iterator::operator++(int)
{
    auto temp{*this};
    _n = _n->next;

    return temp;
}

template<class T> MyList<T>::reference MyList<T>::iterator::operator*()
{
    return _n->data;
}

template<typename T>
MyList<T>::MyList()
    : _tail{static_cast<Node*>(operator new(sizeof(Node)))}, _head{_tail},
      _size{0}
{
    _head->next = _tail;
    _tail->prev = _head;
}

template<typename T> MyList<T>::MyList(MyList& other) : MyList()
{
    for (const auto& x : other) this->push_back(x);
    _size = other._size;
}

template<typename T> MyList<T>::MyList(std::initializer_list<T> init) : MyList()
{
    for (const auto& x : init) this->push_back(x);
    _size = init.size();
}

template<class T> MyList<T>& MyList<T>::operator=(MyList& other)
{
    auto temp{other};
    swap(temp);

    return *this;
}

template<class T>
MyList<T>& MyList<T>::operator=(std::initializer_list<T> ilist)
{
    auto temp{ilist};
    swap(temp);

    return *this;
}

template<class T> MyList<T>::reference MyList<T>::front()
{
    return _head->data;
}

template<class T> MyList<T>::reference MyList<T>::back()
{
    return _tail->prev->data;
}

template<class T> MyList<T>::iterator MyList<T>::begin() noexcept
{
    return iterator{_head};
}

template<class T> MyList<T>::iterator MyList<T>::end() noexcept
{
    return iterator{_tail};
}

template<class T> MyList<T>::reverse_iterator MyList<T>::rbegin() noexcept
{
    return _tail;
}

template<class T> MyList<T>::reverse_iterator MyList<T>::rend() noexcept
{
    return _head;
}

template<class T> bool MyList<T>::empty() const noexcept
{
    return _head == _tail;
}

template<class T> MyList<T>::size_type MyList<T>::size() const noexcept
{
    return _size;
}

template<class T> void MyList<T>::clear() noexcept
{
    while (_head != _tail)
    {
        auto temp{_head};
        _head = _head->next;
        delete temp;
    }
    _size = 0;
}

template<class T>
MyList<T>::iterator MyList<T>::insert(iterator pos, const T& value)
{
    ++_size;

    if (pos == begin())
    {
        auto temp{new Node{value, nullptr, _head}};
        _head = temp;
        return _head;
    }

    return {pos.current()->prev = pos.current()->prev->next =
                new Node{value, pos.current()->prev, pos.current()}};
}

template<class T> MyList<T>::iterator MyList<T>::erase(iterator pos)
{
    auto temp = pos;
    ++temp;
    if (pos == _head)
    {
        _head = _head->next;
        _head->next->prev = nullptr;
    }
    else
    {
        pos.current()->prev->next = pos.current()->next;
        pos.current()->next->prev = pos.current()->prev;
    }
    --_size;

    delete pos.current();

    return temp;
}

template<class T>
MyList<T>::iterator MyList<T>::erase(iterator first, iterator last)
{
    while (first != last)
    {
        auto temp{first};
        ++first;
        erase(temp);
    }

    return last;
}

template<class T> void MyList<T>::push_back(const T& value)
{
    if (!_size)
    {
        _head = new Node{value, nullptr, _tail};
        _tail->prev = _head;
    }
    else _tail->prev = _tail->prev->next = new Node{value, _tail->prev, _tail};
    ++_size;
}

template<class T> void MyList<T>::pop_back()
{
    if (_size == 1)
    {
        delete _head;
        _head = _tail;
        --_size;
    }
    else this->erase(--end());
}

template<class T> void MyList<T>::push_front(const T& value)
{
    insert(begin(), value);
}

template<class T> void MyList<T>::pop_front()
{
    erase(begin());
}

template<class T> void MyList<T>::reverse() noexcept
{
    auto first{begin()};
    auto last{--end()};

    while (first != last && first.current()->prev != last.current())
    {
        std::swap(*first, *last);
        ++first;
        --last;
    }
}

template<class T> MyList<T>::~MyList()
{
    clear();
    operator delete(_tail);
}

template<class T> void MyList<T>::swap(MyList& other) noexcept
{
    std::swap(_head, other._head);
    std::swap(_tail, other._tail);
    std::swap(_size, other._size);
}

template<class T> void swap(MyList<T>& first, MyList<T>& second)
{
    first.swap(second);
}

template<class T> std::size_t MyList<T>::count_positive()
{
    std::size_t res{};

    for (const auto& x : *this)
        if (x > 0) ++res;

    return res;
}

template<class T> MyList<T>::value_type MyList<T>::find_max()
{
    auto max = std::numeric_limits<T>::min();

    for (const auto& x : *this)
        if (x > max) max = x;

    return max;
}

template<class T> std::size_t MyList<T>::count_max_elems()
{
    std::size_t res{};
    auto max = find_max();

    for (const auto& x : *this)
        if (x == max) ++res;

    return res;
}

template<class T> std::pair<MyList<T>, MyList<T>> MyList<T>::split()
{
    MyList<T> negs;
    MyList<T> non_negs;

    auto it = negs.begin();
    auto it2 = non_negs.begin();
    auto it_base = begin();

    while (it_base != end())
    {
        if (*it_base < 0)
        {
            auto n = it_base._n->next;
            it_base._n->prev = it._n->prev;
            it_base._n->next = it._n->next;
            ++it;
            it_base = n;
            ++negs._size;
        }
        else
        {
            auto n = it_base._n->next;
            it_base._n->prev = it2._n->prev;
            it_base._n->next = it2._n->next;
            it2._n->next = it_base._n;
            ++it2;
            it_base = n;
            ++non_negs._size;
        }
        --_size;
    }

    return {negs, non_negs};
}




// ____________________________ БОНУСНОЕ ЗАДАНИЕ
// ____________________________
//     Для бонусного задания необходимо реализовать конструкторы,
//     работающие с move семантикой
// MyList(MyList&& other) noexcept;
// MyList& operator=(MyList&& other) noexcept;

//     И методы добавления элементов

// iterator insert(iterator pos, T&& value);
// void push_back(T&& value);
// void push_front(T&& value);

//     ИЛИ использовать универсальную ссылку и std::forward вместо
//     обычных методов
//     (https://en.cppreference.com/w/cpp/utility/forward) Подробное
//     введение в rvalue-ссылки (https://habr.com/ru/articles/322132/)

// template<typename U>
// iterator insert(iterator pos, U&& value);
// template<typename U>
// void push_back(U&& value);
// template<typename U>
// void push_front(U&& value);