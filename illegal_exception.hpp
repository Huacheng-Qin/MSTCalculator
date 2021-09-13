#ifndef ILLEGAL_EXCEPTION_HPP
#define ILLEGAL_EXCEPTION_HPP
#include <iostream>

class illegal_exception {
    public:
    illegal_exception() = delete;
    illegal_exception(std::string what_arg):
        m_what(std::move(what_arg)) {}
    ~illegal_exception() = default;
    const std::string& what() const {return m_what;}

    private:
    const std::string m_what;
};

#endif
