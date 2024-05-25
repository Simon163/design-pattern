#include <iostream>
#include "nocopyable.h"

/* 
   hungry mode using new operator, meaning that the instance of Sinleton is created once the program starts.
   thread safety can be guaranteed in this mode.
*/
class Singleton:nocopyable
{
public:
    // get the object of singleton instance
    static Singleton*& getInstance();

    // deintialize
    static void deleteInstance();

    // print address of the object of singleton instance
    void print();

private:
    static Singleton* instance;
};

// thread safe because a singleton instance is created once the program starts
Singleton* Singleton::instance = new (std::nothrow)Singleton;

Singleton*& Singleton::getInstance()
{
    return instance;
}

void Singleton::deleteInstance()
{
    if (instance)
    {
        delete instance;
        instance = nullptr;
    }
}

void Singleton::print()
{
    std::cout << "The address of the singleton instance:" << this << std::endl;
}