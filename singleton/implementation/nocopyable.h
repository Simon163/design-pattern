
#pragma once

#include <iostream>

/*
    class nocopyable is used to
    forbid external copy/assignment construction
*/
class nocopyable {
protected:
    nocopyable() {std::cout << "===nocopyable: constructor" << std::endl;};
    ~nocopyable() {std::cout << "===nocopyable: deconstructor" << std::endl;};
public:
    nocopyable(const nocopyable& other) = delete;
    nocopyable& operator = (const nocopyable& other) = delete;
};
