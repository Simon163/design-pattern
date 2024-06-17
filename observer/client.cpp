
#include <iostream>
#include "observer.h"

int main() {

    ConcreteObserved observed;
    IObserver* observerA = new ObserverA();
    observed.add(observerA);
    IObserver* observerB = new ObserverB();
    observed.add(observerB);
    observed.notifyObserver();

    observed.remove(observerA);
    observed.notifyObserver();

    observed.remove(observerB);
    observed.notifyObserver();

    observed.add(nullptr);
    observed.remove(nullptr);
    return 0;
}