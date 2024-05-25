/*
 *  testSuite.cpp
 *  
 *  Copyright (C) 2024
 *  Author: Simon (dewen.wu@gmail.com)
 *  
 */

#include <string.h>
#include "testSuite.h"


TestSuite* TestSuite::instance = nullptr;

TestSuite* TestSuite::get() {
    if (instance == nullptr)
        instance = new TestSuite;
    return instance;
}

TestSuite::TestSuite() {}

TestSuite::~TestSuite() {
    for (int i = 0; i < mTests.size(); ++i) {
        delete mTests[i];
    }
    mTests.clear();

    if (instance) {
        delete instance;
        instance = nullptr;
    }
}

void TestSuite::add(TestCase* test, std::string name) {
    test->name = name;
    mTests.emplace_back(test);
}

void TestSuite::run(std::string name) {
    if (name.length() == 0)
        return;

    auto suite         = TestSuite::get();
    for (int i = 0; i < suite->mTests.size(); ++i) {
        TestCase* test = suite->mTests[i];
        if (test->name.find(name) != std::string::npos) {
            printf("====running %s.\n", test->name.c_str());

            auto res = test->run();
            if (res) {
                printf("The test case: <%s> failed.\n", test->name.c_str());
            }
            else {
                printf("The test case: <%s> passed.\n", test->name.c_str());
            }
        }
    }
}

void TestSuite::runAll() {
    auto suite = TestSuite::get();
    std::vector<std::string> wrongs;
    printf("#Total test cases: %d.\n", (int)suite->mTests.size());
    for (int i = 0; i < suite->mTests.size(); ++i) {
        TestCase* test = suite->mTests[i];
        if (test->name.find("skip") != std::string::npos) {
            // skip test
            continue;
        }
        printf("====Running %d-th test case: %s.\n", i, test->name.c_str());
        auto res = test->run();
        if (res) {
            wrongs.emplace_back(test->name);
        }
    }
    if (wrongs.empty()) {
        printf("All test cases passed.\n");
    }
    else {
        printf("%d test case(s) failed:\n", (int)wrongs.size());
    }
    for (auto& wrong : wrongs) {
        printf("Error: %s\n", wrong.c_str());
    }
}


void unitTest(const char* name) {
    if (name) {
        TestSuite::run(name);
    }
    else {
        TestSuite::runAll();
    }
}
