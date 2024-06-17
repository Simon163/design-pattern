
#pragma once

#include <iostream>
#include <vector>
#include <algorithm>

// abstract observer inteface
class IObserver {
 public:
    virtual void feedback() const = 0;
    virtual ~IObserver() {}
};

// concrete observer A
class ObserverA : public IObserver {
 public:
    ObserverA() {
        std::cout << "ObserverA is created." << std::endl;
    }
    void feedback() const override {
        std::cout << "ObserverA is working: " << this << std::endl;
    }
};

// concrete observer B
class ObserverB : public IObserver {
 public:
    ObserverB() {
        std::cout << "ObserverB is created." << std::endl;
    }
    void feedback() const override {
        std::cout << "ObserverB is working: " << this << std::endl;
    }
};

// abstract oberved interface
class Observed {
 protected:
    std::vector<IObserver*> observers;

 public:
    void add(IObserver* observer) {
        if (observer == nullptr) {
            std::cout << "Error: try to add an invalid observer." << std::endl;
            return;
        }
        observers.push_back(observer);
    }

    void remove(IObserver* observer) {
        if (observer == nullptr) {
            std::cout << "Error: try to remove an invalid observer." << std::endl;
            return;
        }

        if (observers.empty()) {
            std::cout << "Observer list is empty." << std::endl;
            return;
        }

        auto it = std::find(observers.begin(), observers.end(), observer);
        if (it != observers.end()) {
            std::cout << "Observer: " << *it << " is removed from the observer list." << std::endl;
            observers.erase(it);
        } else {
            std::cout << "Observer: " << *it << " is not in the observer list." << std::endl;
        }
    }

    virtual void notifyObserver() = 0;
    virtual ~Observed() {
        for (auto observer : observers) {
            delete observer;
            observer = nullptr;
        }
        observers.clear();
    }
};

// concrete observed
class ConcreteObserved : public Observed {
 public:
    void notifyObserver() override {
        if (observers.empty()) {
            std::cout << "Observer list is empty." << std::endl;
            return;
        }
        for (const auto observer : observers) {
            observer->feedback();
        }
    }
};

