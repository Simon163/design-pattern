
#include "testSuite.h"

int main() {
    // test the specified test case
    const char* casename = "OPTEST1";
    unitTest(casename);

    // test all registered test cases
    unitTest(nullptr);

    return 0;
}