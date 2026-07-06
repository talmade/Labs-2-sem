#include "testset.h"

int main() {
    TestSet tests;
    tests.runAllTests();
    return tests.hasFailed();
}
