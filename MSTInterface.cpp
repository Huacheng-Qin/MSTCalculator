#include <iostream>
#include <string>
#include "illegal_exception.hpp"
#include "MSTInterface.hpp"

bool MSTInterface::Parse(std::string command, std::string input) {
    if (command == "n") {
        m_MST.Initialize(std::stoul(input));
        std::cout << "success" << std::endl;
    } else if (command == "i") {
        Insert(std::move(input));
    } else if (command == "e") {
        Erase(std::move(input));
    } else if (command == "adjacent") {
        Adjacent(std::move(input));
    } else if (command == "degree") {
        Degree(std::stoul(input));
    } else if (command == "edge_count") {
        std::cout << "edge count is " << m_MST.Edges() << std::endl;
    } else if (command == "clear") {
        m_MST.Clear();
        std::cout << "success" << std::endl;
    } else if (command == "mst") {
        Calculate(std::stoul(input));
    } else if (command == "exit") {
        return false;
    } else if (std::cin.eof()) {
        return false;
    }

    return true;
}

void MSTInterface::Insert(std::string input) {
    std::size_t pos1 = input.find_first_of(';');
    std::size_t pos2 = input.find_last_of(';');
    std::size_t arg1 = std::stoul(input.substr(0, pos1));
    std::size_t arg2 = std::stoul(input.substr(pos1 + 1, pos2 - pos1 - 1));
    double arg3 = std::stod(input.substr(pos2 + 1, input.length() - pos2 - 1));
    
    if (arg1 < 0 || arg2 < 0 || arg1 >= m_MST.Nodes() || arg2 >= m_MST.Nodes() || arg1 == arg2 || arg3 <= 0.00) {
        throw illegal_exception("illegal argument");
    }

    m_MST.Insert(arg1, arg2, arg3);
    std::cout << "success" << std::endl;
}

void MSTInterface::Erase(std::string input) {
    std::size_t pos = input.find_first_of(';');
    std::size_t arg1 = std::stoul(input.substr(0, pos));
    std::size_t arg2 = std::stoul(input.substr(pos + 1, input.length() - pos - 1));
    
    if (arg1 < 0 || arg2 < 0 || arg1 >= m_MST.Nodes() || arg2 >= m_MST.Nodes() || arg1 == arg2) {
        throw illegal_exception("illegal argument");
    }

    if (m_MST.Erase(arg1, arg2)) {
        std::cout << "success" << std::endl;
    } else {
        std::cout << "failure" << std::endl;
    }
}

void MSTInterface::Adjacent(std::string input) const {
    std::size_t pos1 = input.find_first_of(';');
    std::size_t pos2 = input.find_last_of(';');
    std::size_t arg1 = std::stoul(input.substr(0, pos1));
    std::size_t arg2 = std::stoul(input.substr(pos1 + 1, pos2 - pos1 - 1));
    double arg3 = std::stod(input.substr(pos2 + 1, input.length() - pos2 - 1));
    
    if (arg1 < 0 || arg2 < 0 || arg1 >= m_MST.Nodes() || arg2 >= m_MST.Nodes() || arg1 == arg2 || arg3 <= 0.00) {
        throw illegal_exception("illegal argument");
    }

    if (m_MST.Adjacent(arg1, arg2, arg3)) {
        std::cout << "adjacent " << arg1 << " " << arg2 << " " << arg3 << std::endl;
    } else {
        std::cout << "not adjacent " << arg1 << " " << arg2 << " " << arg3 << std::endl;
    }
}

void MSTInterface::Degree(std::size_t node) const {
    if (node < 0 || node >= m_MST.Nodes()) {
        throw illegal_exception("illegal argument");
    }

    std::cout << "degree of " << node << " is " << m_MST.Degree(node) << std::endl;
}

void MSTInterface::Calculate(std::size_t node) {
    if (node < 0 || node >= m_MST.Nodes()) {
        throw illegal_exception("illegal argument");
    }

    double weight = m_MST.Calculate(node);
    if (weight == -1.0) {
        std::cout << "not connected" << std::endl;
    } else {
        std::cout << "mst " << weight << std::endl;
    }
}