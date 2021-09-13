#ifndef MSTCALCULATOR_HPP
#define MSTCALCULATOR_HPP
#include <iostream>
#include <vector>

class MSTCalculator {
    public:
    MSTCalculator();
    ~MSTCalculator();
    void Initialize(std::size_t size);
    void Insert(std::size_t u, std::size_t v, double w);
    bool Erase(std::size_t u, std::size_t v);
    bool Adjacent(std::size_t u, std::size_t v, double w) const;
    std::size_t Degree(std::size_t u) const;
    double Calculate(std::size_t u);
    std::size_t Nodes() const;
    std::size_t Edges() const;
    void Clear();

    private:
    std::size_t m_nodes;
    std::size_t m_edges;
    std::vector<std::size_t>* m_edgeMatrix;
    double* m_weightMatrix;
};

#endif
