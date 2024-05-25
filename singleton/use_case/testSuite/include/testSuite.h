/*
 *  testSuite.h
 *  
 *  Copyright (C) 2024
 *  Author: Simon (dewen.wu@gmail.com)
 *  
 */

#pragma once

#include <string>
#include <vector>

/* test case */
class TestCase {
    friend class TestSuite;

public:
    /*
     * @brief deinitializer
     */
    virtual ~TestCase() = default;
    /*
     * @brief run test case
     */
    virtual int run() = 0;

private:
    /* case name */
    std::string name;
};

/* test suite */
class TestSuite {
public:
    /*
     * @brief get shared instance
     * @return shared instance
     */
    static TestSuite* get();

public:
    /*
     * @brief register runable test case
     * @param test test case
     * @param name case name
     */
    void add(TestCase* test, std::string name);
    /*
     * @brief run all registered test case
     */
    static void runAll();
    /*
     * @brief run registered test case that matches in name
     * @param name case name
     */
    static void run(std::string name);

private:
    // forbid external construction
    TestSuite();

    // forbid external deconstruction
    ~TestSuite();

public:
    // forbid external copy construction
    TestSuite(const TestSuite& other) = delete;

    // forbid external assignment operator construction
    const TestSuite& operator= (const TestSuite& other) = delete;

private:
    /* get shared instance */
    static TestSuite* instance;
    /* registered test cases */
    std::vector<TestCase*> mTests;
};

/*
 static register for test case
 */
template <class Case>
class TestRegister {
public:
    /*
     * @brief initializer. register test case to suite.
     * @param name test case name
     */
    TestRegister(std::string name) {
        TestSuite::get()->add(new Case, name);
    }
    /*
     * @brief deinitializer
     */
    ~TestRegister() {
    }
};

#define TESTREGISTER(Case, name) static TestRegister<Case> __##Case(name)

#define TEST_ASSERT(x)                                           \
    {                                                            \
        int res = (x);                                           \
        if (res) {                                               \
            printf("Return error for test case, %s, %d\n", __FUNCTION__, __LINE__); \
            return false;                                        \
        }                                                        \
    }


#ifdef __cplusplus
extern "C" {
#endif

void unitTest(const char* name);

#ifdef __cplusplus
}
#endif
