#include <iostream>
#include "MSTCalculator.hpp"
#include "MinPriorityQueue.hpp"

MSTCalculator::MSTCalculator():
    m_nodes(0), m_edges(0), m_edgeMatrix(nullptr), m_weightMatrix(nullptr) {}

MSTCalculator::~MSTCalculator() {
    if (m_edgeMatrix) {
        delete[] m_edgeMatrix;
    }
    if (m_weightMatrix) {
        delete[] m_weightMatrix;
    }
}

void MSTCalculator::Initialize(std::size_t size) {
    m_nodes = size;
    m_edgeMatrix = new std::vector<std::size_t>[size];
    m_weightMatrix = new double[size*size];
    for (std::size_t i = 0; i < size; i++) {
        m_edgeMatrix[i].reserve(size);
        for (std::size_t j = 0; j < size; j++) {
            m_weightMatrix[i*size + j] = -1;
        }
    }
}

void MSTCalculator::Insert(std::size_t u, std::size_t v, double w) {
    for (std::size_t i:m_edgeMatrix[u]) {
        if (i == v) {
            m_weightMatrix[u*m_nodes + v] = w;
            m_weightMatrix[v*m_nodes + u] = w;
            return;
        }
    }

    m_edgeMatrix[u].push_back(v);
    m_edgeMatrix[v].push_back(u);
    m_weightMatrix[u*m_nodes + v] = w;
    m_weightMatrix[v*m_nodes + u] = w;
    m_edges += 2;
}

bool MSTCalculator::Erase(std::size_t u, std::size_t v) {
    if (m_weightMatrix[u*m_nodes + v] == -1) {
        return false;
    }

    for (std::size_t i = 0; i < m_edgeMatrix[u].size(); i++) {
        if (m_edgeMatrix[u][i] == v) {
            m_edgeMatrix[u].erase(m_edgeMatrix[u].begin() + i);
        }
    }
    for (std::size_t i = 0; i < m_edgeMatrix[v].size(); i++) {
        if (m_edgeMatrix[v][i] == u) {
            m_edgeMatrix[v].erase(m_edgeMatrix[v].begin() + i);
        }
    }
    m_weightMatrix[u*m_nodes + v] = -1;
    m_weightMatrix[v*m_nodes + u] = -1;
    m_edges -= 2;

    return true;
}

bool MSTCalculator::Adjacent(std::size_t u, std::size_t v, double w) const {
    return (m_weightMatrix[u*m_nodes + v] == w) ? true : false;
}

std::size_t MSTCalculator::Degree(std::size_t u) const {
    return m_edgeMatrix[u].size();
}

double MSTCalculator::Calculate(std::size_t u) {
    MinPriorityQueue queue(m_nodes);
    bool complete[m_nodes];
    double weight = 0.0;

    for (std::size_t i = 0; i < m_nodes; i++) {
        complete[i] = false;
    }
    queue.Insert(u, 0.0);

    while (!queue.Empty()) {
        weight += queue.Min();
        u = queue.PopMin();
        complete[u] = true;
        for (std::size_t i:m_edgeMatrix[u]) {
            if (!complete[i]) {
                queue.Insert(i, m_weightMatrix[u*m_nodes + i]);
            }
        }
    }

    for (std::size_t i = 0; i < m_nodes; i++) {
        if (!complete[i]) {
            return -1;
        }
    }

    return weight;
}

std::size_t MSTCalculator::Nodes() const {
    return m_nodes;
}

std::size_t MSTCalculator::Edges() const {
    return m_edges;
}

void MSTCalculator::Clear() {
    m_edges = 0;
    for (std::size_t i = 0; i < m_nodes; i++) {
        m_edgeMatrix[i].clear();
        for (std::size_t j = 0; j < m_nodes; j++) {
            m_weightMatrix[i*m_nodes + j] = -1;
        }
    }
}
