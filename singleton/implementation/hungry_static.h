#include <iostream>
#include "nocopyable.h"

/*
    hungry mode using static variable, meaning that the instance of Sinleton is created once the program starts.
    thread safety can be guaranteed in this mode.

*/
class Singleton:nocopyable
{
public:
    // get the object of singleton instance
    static Singleton& getInstance();

    // print address of the object of singleton instance
    void print();
};

Singleton& Singleton::getInstance()
{
    // create singleton instance using static
    static Singleton instance;
    return instance;
}

void Singleton::print()
{
    std::cout << "The address of this object of singleton instance:" << this << std::endl;
}