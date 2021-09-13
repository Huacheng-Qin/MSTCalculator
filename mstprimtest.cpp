#include <iostream>
#include <string>
#include <iomanip>
#include "illegal_exception.hpp"
#include "MSTInterface.hpp"
#include <vector>

int main() {
    MSTInterface parser;
    std::string command;
    std::string input;
    bool loop = true;
    std::cout << std::fixed << std::setprecision(2);

    while (loop) {
        std::cin >> command;
        std::getline(std::cin, input);
        try {
            loop = parser.Parse(std::move(command), std::move(input));
        } catch (illegal_exception e) {
            std::cout << e.what() << std::endl;
        }
    }

    return 0;
}
