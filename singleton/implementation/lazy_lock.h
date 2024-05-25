#include <iostream>
#include <mutex>
#include "nocopyable.h"

/* 
    lazy mode, meaning that the instance of Sinleton is created only when it is first needed.
    double-checked locking is used to ensure thread safety in multi-threaded environments.
*/
class Singleton:nocopyable
{
public:
    // get the object of singleton instance
    static Singleton*& getInstance();

    // deinitialize
    static void deleteInstance();

    // print address of the object of singleton instance
    void print();

private:
    static Singleton* instance;
    static std::mutex mutex;
};

// initialize
Singleton* Singleton::instance = nullptr;
std::mutex Singleton::mutex;

Singleton*& Singleton::getInstance()
{

    // double-checked locking
    if (instance == nullptr) {
        std::unique_lock<std::mutex> lock(mutex); // locking
        if (instance == nullptr) {
            instance = new (std::nothrow)Singleton;
        }
    }

    return instance;
}

void Singleton::deleteInstance()
{
    std::unique_lock<std::mutex> lock(mutex); // locking
    if (instance) {
        delete instance;
        instance = nullptr;
    }
}

void Singleton::print()
{
    std::cout << "The address of the singleton instance:" << this << std::endl;
}