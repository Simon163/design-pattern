#pragma once

#include <iostream>
#include <memory>

// abstract iterator interface
template <typename T2>
class Iterator {
 public:
    virtual ~Iterator() {}
    virtual bool hasNext() const = 0;
    virtual T2 next() = 0;
};

// concrete iterator implementation
template <typename T1, typename T2>
class ConcreteIterator : public Iterator<T2> {
 private:
    typename T1 :: const_iterator iter, end;
 public:
    explicit ConcreteIterator(const T1& container)
        : iter(container.begin()), end(container.end()) {}

    // check if there are more elements in the container
    bool hasNext() const override {
        return iter != end;
    }

    // return the next element in the container and increment the iterator
    T2 next() override {
        if (hasNext()) {
            return *iter++;
        }
        throw std::out_of_range("No more elements");
    }
};

// abstract container interface
template <typename T1, typename T2>
class Container {
 public:
    virtual ~Container() {}
    virtual std::unique_ptr<Iterator<T2>> createIterator() const = 0;
};

// concrete container implementation
template <typename T1, typename T2>
class ConcreteContainer : public Container<T1, T2> {
 private:
    T1 data_;
 public:
    explicit ConcreteContainer(const T1& data) : data_(data) {}

    std::unique_ptr<Iterator<T2>> createIterator() const override {
        return std::make_unique<ConcreteIterator<T1, T2>>(data_);
    }
};
