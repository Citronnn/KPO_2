#ifndef PRIORITYQUEUECONTAINER_H
#define PRIORITYQUEUECONTAINER_H
#include "headers.h"
#include "priorityQueueExceptions.h"
template<typename T, class Container = std::vector<QPair<int, T>>>
class PriorityQueue;

template <typename T>
class PriorityQueueIterator {
public:
    PriorityQueueIterator (typename std::vector<QPair<int, T>>::reverse_iterator ptr_, bool empty) : ptr(ptr_), isEmpty(empty) {}
    QPair<int, T>& operator*()
    {
        if (isEmpty) {
            throw QueueInvalidIterator<T>(isEmpty, ptr);
        }
        return *ptr;
    }
    const typename std::vector<QPair<int, T>>::reverse_iterator operator->() {
        if (isEmpty) {
            throw QueueInvalidIterator<T>(isEmpty, ptr);
        }
        return ptr;
    }
    typename std::vector<QPair<int, T>>::reverse_iterator operator++() {
        return ++ptr;
    }
    PriorityQueueIterator operator++(int) {
        PriorityQueueIterator<T> orig = *this;
        ++(*this);
        return orig;
    }
    typename std::vector<QPair<int, T>>::reverse_iterator operator--() {
        return --ptr;
    }
    PriorityQueueIterator operator--(int) {
        PriorityQueueIterator<T> orig = *this;
        --(*this);
        return orig;
    }
    bool operator==(const PriorityQueueIterator& other) const {
        return ptr == other.ptr;
    }
    bool operator!=(const PriorityQueueIterator& other) const {
        return !(*this == other);
    }
private:
    typename std::vector<QPair<int, T>>::reverse_iterator ptr;
    bool isEmpty;
};

template<typename T, class Container>
class PriorityQueue {
public:
    friend class PriorityQueueIterator<T>;
    void push(T const& lhs, int priority) {
        if (!elements.size() || elements.back().first < priority) {
             elements.push_back(qMakePair(priority,lhs));
        }
        else {
           // std::sort(elements.begin(), elements.end(), comparePairs<int, T>);
           for (int i = 0; i < elements.size(); i++) {
               if (elements[i].first > priority) {
                   elements.insert(elements.begin() + i, qMakePair(priority,lhs));
                   break;
               }
           }
        }
    }
    void push(T const& lhs) {
        if (elements.size()){
            elements.push_back(qMakePair(elements.back().first + 1,lhs));
        } else {
            elements.push_back(qMakePair(1,lhs));
        }
    }
    void pop() {
         if (empty()) {
            throw QueueBlank<T>(elements);
        }
        elements.pop_back();
    }
    T const& top() const {
        if (empty()) {
            throw QueueBlank<T>(elements);
        }
        return elements.back().second;
    }
    typedef typename Container::size_type size_type;
    size_type size() const {
        return elements.size();
    }
    bool empty() const {
        return elements.empty();
    }
    PriorityQueueIterator<T> begin() {
        return PriorityQueueIterator<T>(elements.rbegin(), empty());
    }
    PriorityQueueIterator<T> end() {
        return PriorityQueueIterator<T>(elements.rend(), empty());
    }
private:
    Container elements;
};

#endif // PRIORITYQUEUECONTAINER_H
