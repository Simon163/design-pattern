Factory patterns can be categorized into three similar types, arranged in order from the simplest to the most complex:

## [Simple Factory Pattern](simple_factory)

The Simple Factory Pattern is a basic factory design pattern that provides an interface for creating objects but does not specify which class to instantiate. Instead, this task is delegated to the factory class. This factory class usually contains a static method that decides which specific class instance to create and return based on the parameters passed in. Its advantage lies in simplifying the client code, as the client does not need to understand the creation process of specific products. However, it also has obvious drawbacks, such as violating the open-closed principle because adding new products requires modifying the factory class code.

## [Factory Method Pattern](factory)

The Factory Method Pattern is a further abstraction of the Simple Factory Pattern. It defines an interface for creating objects, but the subclass decides which class to instantiate. In other words, the Factory Method Pattern allows subclasses to decide which product objects to create instead of hardcoding this decision in the factory class. This approach improves the system's extensibility since adding new products only requires adding the corresponding factory subclass and product class without modifying existing code, thus adhering to the open-closed principle.

## [Abstract Factory Pattern](abstract_factory)

The Abstract Factory Pattern is the most complex of all factory patterns. It provides an interface for creating a set of related or interdependent objects without specifying their concrete classes. The Abstract Factory Pattern can create not only a single product but also a family of related products. Each concrete factory corresponds to a product family and can create a family of products. It is suitable for systems that need multiple product series, where each series can change or expand independently. However, the downside is that adding a new product family requires modifying the interface.