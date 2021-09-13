#include <iostream>
#include "MinPriorityQueue.hpp"

MinPriorityQueue::MinPriorityQueue(std::size_t max_size):
    m_size(0), m_max(max_size), m_location(new std::size_t[max_size]), m_heap(new Node[max_size]) {
    for (std::size_t i = 0; i < max_size; i++) {
        m_location[i] = std::string::npos;
    }
}

MinPriorityQueue::~MinPriorityQueue() {
    if(m_heap) {
        delete[] m_heap;
    }
    if (m_location) {
        delete[] m_location;
    }
}

void MinPriorityQueue::Insert(std::size_t key, double weight) {
    if (key >= m_max) {
        return;
    }

    std::size_t pos = m_location[key];
    if (pos == std::string::npos) {
        m_heap[m_size] = {key, weight};
        m_location[key] = m_size;
        m_size++;
        pos = m_size/2;
        while (pos > 0) {
            Heapify(pos - 1);
            pos /= 2;
        }
    } else {
        pos++;
        if (weight < m_heap[pos - 1].weight) {
            m_heap[pos - 1].weight = weight;
            while (pos > 0) {
                Heapify(pos - 1);
                pos /= 2;
            }
        }
    }
}

double MinPriorityQueue::Min() const {
    return m_heap[0].weight;
}

std::size_t MinPriorityQueue::PopMin() {
    if (m_size == 0) {
        return std::string::npos;
    }

    std::size_t key = m_heap[0].key;
    m_location[key] = std::string::npos;
    m_size--;
    m_heap[0] = m_heap[m_size];
    m_location[m_heap[0].key] = 0;
    Heapify(0);

    return key;
}

bool MinPriorityQueue::Empty() const {
    return (m_size == 0);
}

void MinPriorityQueue::Heapify(std::size_t pos) {
    std::size_t min;
    if (pos*2 + 1 < m_size) {
        if (pos*2 + 2 < m_size) {
            min = (m_heap[pos*2 + 1].weight < m_heap[pos*2 + 2].weight) ? pos*2 + 1 : pos*2 + 2;
        } else {
            min = pos*2 + 1;
        }
    } else {
        return;
    }

    if (m_heap[min].weight < m_heap[pos].weight) {
        m_location[m_heap[pos].key] = min;
        m_location[m_heap[min].key] = pos;
        Node hold = m_heap[pos];
        m_heap[pos] = m_heap[min];
        m_heap[min] = hold;
        Heapify(min);
    }
}