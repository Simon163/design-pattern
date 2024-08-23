# design-pattern
This repo is used to provide the C++ implemention of common design patterns.

## Creational Design Patterns
###  [Singleton](singleton/singleton.md)
###  [Factory](factory/factory.md)
###  [Builder](builder/builder.md)
###  [Prototype](prototype/prototype.md)

## Structural Design Patterns
###  [Decorator](decorator/decorator.md)
###  [Adapter](adaptor/adaptor.md)
###  Bridge
###  Composite
###  Facade
###  Proxy
###  Flyweight

## Behavioral Design Patterns
###  [Iterator](iterator/iterator.md)
###  [Observer](observer/observer.md)
###  [Chain of responsiblity](chain_of_responsiblity/chain_of_responsiblity.md)
###  [Strategy](strategy/strategy.md)
###  [State](state/state.md)
###  Command
###  Mediator
###  Memento
###  Template
###  Visitor

## Build and run
Build:

Take the Adaptor pattern as an example:
```
cd adaptor
mkdir build && cd build
cmake .. && make
```
Run:
```
./client.out
```