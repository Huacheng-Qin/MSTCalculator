#ifndef MINPRIORITYQUEUE_HPP
#define MINPRIORITYQUEUE_HPP
#include <iostream>

class MinPriorityQueue {
    public:
    MinPriorityQueue() = delete;
    MinPriorityQueue(std::size_t max_size);
    ~MinPriorityQueue();
    void Insert(std::size_t key, double weight);
    double Min() const;
    std::size_t PopMin();
    bool Empty() const;

    private:
    void Heapify(std::size_t pos);

    struct Node {
        std::size_t key;
        double weight;
    };
    std::size_t m_size;
    std::size_t m_max;
    std::size_t* m_location;
    Node* m_heap;
};

#endif