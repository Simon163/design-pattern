# design pattern
## singleton
Singleton is a popular design pattern that ensures that only one instance of a class can exist in the entire program, namely, there is only one global access to the instance of a singleton class throughout the lifetime of the program.

### implementation
To achieve only one global access, the constructor and deconstructor should be defined as private.  The copy constructor and assignment operator constructor should be deleted to prevent copying of the singleton instance.

Typically the singleton design pattern can be implemented in two ways: lazy initialization and hungry initialization.

Lazy initialization means the instance of the Sinleton class is created only when it is first needed while hungry initialization means the instance of the Sinleton class is created once the program starts.  The hungry initialization is born with thread safety and lazy initialization is not.  Double-checked locking can be used to ensure threads are safe In lazy mode.

This repo provides two implementations for lazy initialization and hungry initialization respectively.
- lazy initialization: 
	+ singleton/implementation/lazy_lock.h: 
		double-checked locking is used to ensure thread safety in multi-threaded environments.
		
		build: cd singleton/implementation && g++ main.cpp -DLAZY_LOCK -o main -pthread
	+ singleton/implementation/lazy_no_thread_safe.h: 
		no thread safety is ensured in multi-threaded environments.

		build: cd singleton/implementation && g++ main.cpp -DLAZY_NO -o main -pthread
		
- hungry initialization: 
	+ singleton/implementation/hungry_new.h
		The new operator is used to create the instance of the Singleton class.
		
	build: cd singleton/implementation && g++ main.cpp -DHUNGRY_NEW -o main -pthread
	+ singleton/implementation/hungry_static.h
	 The static variable is used to create the instance of the Singleton class.
	 
	 build: cd singleton/implementation && g++ main.cpp -DHUNGRY_STATIC -o main -pthread

[hungry initialization using the static variable](singleton/implementation/hungry_static.h) is recommended to implement the singleton design pattern from the perspective of less amount of code and thread safety guarantees.

### use case
This repo provides a use case for applying the singleton design pattern to implement the functionality test of operators in the machine learning domain.

To register a test case, use TESTREGISTER macro, for example: 
```
TESTREGISTER(opTest1, "OPTEST1");
```
While "opTest1" is the class name of the test case and "OPTEST1" is the name of the test case.

To test a specified test case, give the name of the test case, for example:
```
    const char* casename = "OPTEST1";
    unitTest(casename);
```

To test all registered test cases, just call the unitTest function with nullptr, for example:
```
    unitTest(nullptr);
```

build and run:
```
cd singleton/use_case
mkdir build && cd build
cmake .. && make
./unitTest
```

The test results look like: 

```
====running OPTEST1.
The test case: <OPTEST1> passed.
#Total test cases: 2.
====Running 0-th test case: OPTEST1.
====Running 1-th test case: OPTEST2.
1 test case(s) failed:
Error: OPTEST2