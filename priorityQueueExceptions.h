#ifndef PRIORITYQUEUEEXCEPTIONS_H
#define PRIORITYQUEUEEXCEPTIONS_H
#include "headers.h"
class QueueException {
public:
    QueueException() = default;
    friend inline std::ostream &operator<<(std::ostream &out, QueueException &e){
        e.print(out);
        return out;
    };
    virtual void print(std::ostream& out) = 0;
    virtual ~QueueException() = default;
};

template <typename T>
class QueueInvalidIterator : public QueueException {
public:
    inline QueueInvalidIterator(const bool isEmpty, typename std::vector<QPair<int, T>>::reverse_iterator ptr): isEmpty(isEmpty), ptr(ptr) {
    }
    void print(std::ostream &out) {
        out << "QueueInvalidIterator: " << &ptr;
    }
private:
    typename std::vector<QPair<int, T>>::reverse_iterator ptr;
    bool isEmpty;
};

template <typename T>
class QueueBlank: public QueueException {
public:
    inline QueueBlank(const std::vector<QPair<int, T>>& queue): queue(queue) {
        queueLength = queue.size();
    }
    void print(std::ostream &out) {
        out << "QueueBlank: " << queueLength;
    }
private:
    std::vector<QPair<int, T>> queue;
    std::size_t queueLength;
};

#endif // PRIORITYQUEUEEXCEPTIONS_H
