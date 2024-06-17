
#include <iostream>
#include <vector>
#include <set>
#include "iterator.h"

// traverse elements in container and print them out
template <typename T1, typename T2>
void printElements(const Container<T1, T2>& container) {
    std::unique_ptr<Iterator<T2>> iterator = container.createIterator();
    while (iterator.get()->hasNext()) {
        std::cout << iterator.get()->next() << std::endl;
    }
}

int main() {
    {
        std::vector<int> data = {1, 2, 3, 4, 5, 6, 7};
        ConcreteContainer<std::vector<int>, int> container(data);
        printElements<std::vector<int>, int>(container);
    }

    {
        std::vector<std::string> data = {"a", "ab", "abc", "abcd", "abcde"};
        ConcreteContainer<std::vector<std::string>, std::string> container(data);
        printElements<std::vector<std::string>, std::string>(container);
    }

    {
        std::set<std::string> data = {"a", "ab", "abc", "abcd", "abcde"};
        ConcreteContainer<std::set<std::string>, std::string> container(data);
        printElements<std::set<std::string>, std::string>(container);
    }

    {
        std::array<int, 7> data = {1, 2, 3, 4, 5, 6, 7};
        ConcreteContainer<std::array<int, 7>, int> container(data);
        printElements<std::array<int, 7>, int>(container);
    }
    return 0;
}