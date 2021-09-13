#ifndef MSTINTERFACE_HPP
#define MSTINTERFACE_HPP
#include <iostream>
#include "MSTCalculator.hpp"

class MSTInterface {
    public:
    MSTInterface() = default;
    ~MSTInterface() = default;
    bool Parse(std::string command, std::string input);

    private:
    void Insert(std::string input);
    void Erase(std::string input);
    void Adjacent(std::string input) const;
    void Degree(std::size_t node) const;
    void Calculate(std::size_t node);

    MSTCalculator m_MST;
};

#endif