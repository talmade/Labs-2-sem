#include <sstream>
#include <iostream>

#include "testset.h"
#include "myset.h"

bool TestSet::hasFailed() const {
    return error > 0;
}

void TestSet::check(bool condition) {
    if (!condition)
        throw std::invalid_argument("Check failed");
}

void TestSet::runTest(const char* name, std::function<void()> function) {
    try {
        function();
        std::cout << "OK " << name << "\n";
        succes++;
    } catch (...) {
        std::cout << "FAIL " << name << "\n";
        error++;
    }
}

void TestSet::testConstructor() {
    testDefaultConstructorEmpty();
    testCopyConstructorContainsElements();
    testCopyConstructorSameLength();
    testCopyConstructorIndependent();
    testMoveConstructorTransfersElements();
    testMoveConstructorClearsSource();
    testMoveConstructorEmptySource();
    testInitializerListSkipsDuplicates();
    testInitializerListEmpty();
}

void TestSet::testDefaultConstructorEmpty() {
    runTest(__func__, [this] {
        MySet<int> set;
        check(set.getLength() == 0);
    });
}

void TestSet::testCopyConstructorContainsElements() {
    runTest(__func__, [this] {
        MySet<int> set;
        set.add(1);
        set.add(2);
        MySet<int> copy(set);
        check(copy.contains(1));
        check(copy.contains(2));
    });
}

void TestSet::testCopyConstructorSameLength() {
    runTest(__func__, [this] {
        MySet<int> set;
        set.add(1);
        set.add(2);
        MySet<int> copy(set);
        check(copy.getLength() == set.getLength());
    });
}

void TestSet::testCopyConstructorIndependent() {
    runTest(__func__, [this] {
        MySet<int> source;
        source.add(1);
        source.add(2);
        MySet<int> copy(source);
        source.add(3);
        check(copy.getLength() == 2);
    });
}

void TestSet::testMoveConstructorTransfersElements() {
    runTest(__func__, [this] {
        MySet<int> source;
        source.add(1);
        source.add(2);
        MySet<int> destination(std::move(source));
        check(destination.getLength() == 2);
    });
}

void TestSet::testMoveConstructorClearsSource() {
    runTest(__func__, [this] {
        MySet<int> source;
        source.add(1);
        source.add(2);
        MySet<int> destination(std::move(source));
        check(source.getLength() == 0);
    });
}

void TestSet::testMoveConstructorEmptySource() {
    runTest(__func__, [this] {
        MySet<int> source;
        MySet<int> destination(std::move(source));
        check(destination.getLength() == 0);
    });
}

void TestSet::testInitializerListSkipsDuplicates() {
    runTest(__func__, [this] {
        MySet<int> set({1, 1, 2, 2, 3});
        check(set.getLength() == 3);
    });
}

void TestSet::testInitializerListEmpty() {
    runTest(__func__, [this] {
        MySet<int> set{};
        check(set.getLength() == 0);
    });
}

void TestSet::testGetLength() {
    testGetLengthEmpty();
    testGetLengthFill();
}

void TestSet::testGetLengthEmpty() {
    runTest(__func__, [this] {
        MySet<int> set;
        check(set.getLength() == 0);
    });
}

void TestSet::testGetLengthFill() {
    runTest(__func__, [this] {
        MySet<int> set{1, 2, 3};
        check(set.getLength() == 3);
    });
}

void TestSet::testAdd() {
    testAddIncreasesLength();
    testAddSortedOrder();
    testAddDuplicateIgnored();
}

void TestSet::testAddIncreasesLength() {
    runTest(__func__, [this] {
        MySet<double> set;
        set.add(3.);
        set.add(3.);
        set.add(3.);
        check(set.getLength() == 3);
    });
}

void TestSet::testAddSortedOrder() {
    runTest(__func__, [this] {
        MySet<int> set{4, 5, 6};
        set.add(3);
        set.add(2);
        set.add(1);
        int i = 1;
        for (auto it = set.iteratorBegin(); it != set.iteratorEnd(); ++it) {
            check(it.value() == i);
            i++;
        }
    });
}

void TestSet::testAddDuplicateIgnored() {
    runTest(__func__, [this] {
        MySet<int> set;
        set.add(7);
        set.add(9);
        set.add(9);
        set.add(14);
        int sum = 0;
        for (auto it = set.iteratorBegin(); it != set.iteratorEnd(); ++it)
            sum += *it;
        check(sum == 30);
    });
}

void TestSet::testRemove() {
    testRemoveAllElements();
    testRemoveElementNotInSet();
    testRemoveNonexistentElement();
    testRemoveNodeWithTwoChildren();
}

void TestSet::testRemoveAllElements() {
    runTest(__func__, [this] {
        MySet<int> set;
        set.remove(1);
        set.remove(2);
        set.remove(3);
        check(set.getLength() == 0);
    });
}

void TestSet::testRemoveElementNotInSet() {
    runTest(__func__, [this] {
        MySet<int> set{1, 2, 5, 4, 3, 6};
        set.remove(6);
        set.remove(5);
        set.remove(4);
        int i = 1;
        for (auto it = set.iteratorBegin(); it != set.iteratorEnd(); ++it) {
            check(it.value() == i);
            i++;
        }
    });
}

void TestSet::testRemoveNonexistentElement() {
    runTest(__func__, [this] {
        MySet<int> set{1, 5, 15, 10};
        set.remove(1);
        set.remove(1);
        set.remove(14);
        set.remove(5);
        int sum = 0;
        for (auto it = set.iteratorBegin(); it != set.iteratorEnd(); ++it)
            sum += *it;
        check(sum == 25);
    });
}

void TestSet::testRemoveNodeWithTwoChildren() {
    runTest(__func__, [this] {
        MySet<int> set{5, 3, 7, 2, 4};
        set.remove(3);
        check(!set.contains(3));
        check(set.contains(2));
        check(set.contains(4));
    });
}

void TestSet::testContains() {
    testContainsExistingElement();
    testContainsMissingElement();
    testContainsEmptySet();
}

void TestSet::testContainsExistingElement() {
    runTest(__func__, [this] {
        MySet<int> set{1, 2, 3};
        check(set.contains(1));
    });
}

void TestSet::testContainsMissingElement() {
    runTest(__func__, [this] {
        MySet<int> set{1, 2, 3};
        check(!set.contains(4));
    });
}

void TestSet::testContainsEmptySet() {
    runTest(__func__, [this] {
        MySet<int> set;
        check(!set.contains(1));
    });
}

void TestSet::testClear() {
    testClearEmptySet();
    testClearRemovesAllElements();
    testClearTwice();
    testClearContainsFalse();
}

void TestSet::testClearEmptySet() {
    runTest(__func__, [this] {
        MySet<int> set;
        set.clear();
        check(set.getLength() == 0);
    });
}

void TestSet::testClearRemovesAllElements() {
    runTest(__func__, [this] {
        MySet<int> set{1, 4, 2, 3};
        set.clear();
        check(set.getLength() == 0);
    });
}

void TestSet::testClearTwice() {
    runTest(__func__, [this] {
        MySet<int> set{1, 4, 2, 3};
        set.clear();
        set.clear();
        check(set.getLength() == 0);
    });
}

void TestSet::testClearContainsFalse() {
    runTest(__func__, [this] {
        MySet<int> set{1, 2, 3};
        set.clear();
        check(!set.contains(1));
        check(!set.contains(2));
        check(!set.contains(3));
    });
}

void TestSet::testGetRoot() {
    testGetRootEmpty();
    testGetRootValue();
}

void TestSet::testGetRootEmpty() {
    runTest(__func__, [this] {
        MySet<int> set;
        check(set.getRoot() == nullptr);
    });
}

void TestSet::testGetRootValue() {
    runTest(__func__, [this] {
        MySet<int> set{5, 3, 7};
        check(set.getRoot()->data == 5);
    });
}

void TestSet::testToArray() {
    testToArrayNull();
    testToArrayNotNull();
    testToArraySortedOrder();
}

void TestSet::testToArrayNull() {
    runTest(__func__, [this] {
        MySet<int> set;
        int* array = set.toArray();
        check(set.getLength() == 0);
        delete[] array;
    });
}

void TestSet::testToArrayNotNull() {
    runTest(__func__, [this] {
        MySet<int> set{1, 4, 2, 3};
        int* array = set.toArray();
        check(array);
        delete[] array;
    });
}

void TestSet::testToArraySortedOrder() {
    runTest(__func__, [this] {
        MySet<int> set{1, 4, 2, 3};
        int* array = set.toArray();
        for (size_t i = 1; i < set.getLength(); i++)
            check(array[i - 1] <= array[i]);
        delete[] array;
    });
}

void TestSet::testUnion() {
    testUnionWithEmpty();
    testUnionPartiallyIdentical();
    testUnionPartiallyIdenticalLength();
    testUnionBothEmpty();
}

void TestSet::testUnionWithEmpty() {
    runTest(__func__, [this] {
        MySet<int> set1{1, 4, 2, 3};
        MySet<int> set2{};
        set1.unionSets(set2);
        check(set1.getLength() == 4);
    });
}

void TestSet::testUnionPartiallyIdentical() {
    runTest(__func__, [this] {
        MySet<int> set1{1, 2, 3};
        MySet<int> set2{2, 3, 4};
        set1.unionSets(set2);
        check(set1.contains(4));
    });
}

void TestSet::testUnionPartiallyIdenticalLength() {
    runTest(__func__, [this] {
        MySet<int> set1{1, 2, 3};
        MySet<int> set2{4, 5, 6};
        set1.unionSets(set2);
        check(set1.getLength() == 6);
    });
}

void TestSet::testUnionBothEmpty() {
    runTest(__func__, [this] {
        MySet<int> set1;
        MySet<int> set2;
        set1.unionSets(set2);
        check(set1.getLength() == 0);
    });
}

void TestSet::testIntersection() {
    testIntersectionDisjointSets();
    testIntersectionPartiallyIdentical();
    testIntersectionPartiallyIdenticalContains();
    testIntersectionBothEmpty();
}

void TestSet::testIntersectionDisjointSets() {
    runTest(__func__, [this] {
        MySet<int> set1{1, 2, 3, 4};
        MySet<int> set2{5, 6, 7, 8};
        set1.intersection(set2);
        check(set1.getLength() == 0);
    });
}

void TestSet::testIntersectionPartiallyIdentical() {
    runTest(__func__, [this] {
        MySet<int> set1{1, 2, 3};
        MySet<int> set2{2, 3, 4};
        set1.intersection(set2);
        check(!set1.contains(1));
    });
}

void TestSet::testIntersectionPartiallyIdenticalContains() {
    runTest(__func__, [this] {
        MySet<int> set1{1, 2, 3};
        MySet<int> set2{2, 3, 4};
        set1.intersection(set2);
        check(set1.getLength() == 2);
    });
}

void TestSet::testIntersectionBothEmpty() {
    runTest(__func__, [this] {
        MySet<int> set1;
        MySet<int> set2;
        set1.intersection(set2);
        check(set1.getLength() == 0);
    });
}

void TestSet::testSubtract() {
    testSubtractWithEmpty();
    testSubtractPartiallyIdentical();
    testSubtractPartiallyIdenticalContains();
    testSubtractBothEmpty();
}

void TestSet::testSubtractWithEmpty() {
    runTest(__func__, [this] {
        MySet<int> set1{1, 4, 2, 3};
        MySet<int> set2{};
        set1.subtract(set2);
        check(set1.getLength() == 4);
    });
}

void TestSet::testSubtractPartiallyIdentical() {
    runTest(__func__, [this] {
        MySet<int> set1{1, 2, 3};
        MySet<int> set2{2, 3, 4};
        set1.subtract(set2);
        check(set1.contains(1));
    });
}

void TestSet::testSubtractPartiallyIdenticalContains() {
    runTest(__func__, [this] {
        MySet<int> set1{1, 2, 3};
        MySet<int> set2{3, 4, 5};
        set1.subtract(set2);
        check(set1.getLength() == 2);
    });
}

void TestSet::testSubtractBothEmpty() {
    runTest(__func__, [this] {
        MySet<int> set1;
        MySet<int> set2;
        set1.subtract(set2);
        check(set1.getLength() == 0);
    });
}

void TestSet::testOperatorPlus() {
    testPlusDisjointSets();
    testPlusOverlappingSets();
    testPlusChained();
}

void TestSet::testPlusDisjointSets() {
    runTest(__func__, [this] {
        MySet<int> set1{1, 4, 2, 3};
        MySet<int> set2{5, 6, 7, 8};
        MySet<int> set3 = set1 + set2;
        check(set3.getLength() == 8);
    });
}

void TestSet::testPlusOverlappingSets() {
    runTest(__func__, [this] {
        MySet<int> set1{1, 2, 3};
        MySet<int> set2{2, 3, 4};
        MySet<int> set3 = set1 + set2;
        check(set3.contains(4));
    });
}

void TestSet::testPlusChained() {
    runTest(__func__, [this] {
        MySet<int> set1{1, 2, 3};
        MySet<int> set2{4, 5, 6};
        MySet<int> set3{7, 8, 9};
        MySet<int> set4 = set1 + set2 + set3;
        int i = 1;
        for (auto it = set4.iteratorBegin(); it != set4.iteratorEnd(); ++it) {
            check(it.value() == i);
            i++;
        }
        check(i == 10);
    });
}

void TestSet::testOperatorIntersection() {
    testMultiplyDisjointSets();
    testMultiplyOverlappingSets();
    testMultiplyChained();
}

void TestSet::testMultiplyDisjointSets() {
    runTest(__func__, [this] {
        MySet<int> set1{1, 4, 2, 3};
        MySet<int> set2{5, 6, 7, 8};
        MySet<int> set3 = set1 * set2;
        check(set3.getLength() == 0);
    });
}

void TestSet::testMultiplyOverlappingSets() {
    runTest(__func__, [this] {
        MySet<int> set1{1, 2, 3};
        MySet<int> set2{2, 3, 4};
        MySet<int> set3 = set1 * set2;
        check(set3.getLength() == 2);
    });
}

void TestSet::testMultiplyChained() {
    runTest(__func__, [this] {
        MySet<int> set1{1, 2, 3, 4};
        MySet<int> set2{2, 3, 4, 5};
        MySet<int> set3{3, 4, 5, 6};
        MySet<int> set4 = set1 * set2 * set3;
        check(set4.contains(3));
        check(set4.contains(4));
    });
}

void TestSet::testOperatorSubtract() {
    testDivideRemovesShared();
    testDivideSelfIsEmpty();
    testDivideChained();
}

void TestSet::testDivideRemovesShared() {
    runTest(__func__, [this] {
        MySet<int> set1{1, 4, 2, 3};
        MySet<int> set2{9, 1, 2};
        MySet<int> set3 = set1 / set2;
        check(set3.contains(3));
        check(set3.contains(4));
    });
}

void TestSet::testDivideSelfIsEmpty() {
    runTest(__func__, [this] {
        MySet<int> set{1, 2, 3};
        MySet<int> result = set / set;
        check(result.getLength() == 0);
    });
}

void TestSet::testDivideChained() {
    runTest(__func__, [this] {
        MySet<int> set1{1, 2, 3, 4, 5};
        MySet<int> set2{1, 2};
        MySet<int> set3{3};
        MySet<int> set4 = set1 / set2 / set3;
        check(set4.getLength() == 2);
    });
}

void TestSet::testOperatorPlusEqual() {
    testPlusEqualAddsElements();
    testPlusEqualRvalue();
    testPlusEqualChained();
}

void TestSet::testPlusEqualAddsElements() {
    runTest(__func__, [this] {
        MySet<int> set1{1, 4, 2, 3};
        MySet<int> set2{5, 6, 7, 8};
        set1 += set2;
        int i = 1;
        for (auto it = set1.iteratorBegin(); it != set1.iteratorEnd(); ++it) {
            check(it.value() == i);
            i++;
        }
    });
}

void TestSet::testPlusEqualRvalue() {
    runTest(__func__, [this] {
        MySet<int> set1{1, 2, 3};
        set1 += MySet<int>{4, 5, 6};
        check(set1.getLength() == 6);
    });
}

void TestSet::testPlusEqualChained() {
    runTest(__func__, [this] {
        MySet<int> set1{1, 2, 3};
        MySet<int> set2{4, 5, 6};
        MySet<int> set3{7, 8, 9};
        set1 += set2 += set3;
        check(set1.getLength() == 9);
        check(set2.getLength() == 6);
    });
}

void TestSet::testOperatorMultiplyEqual() {
    testMultiplyEqualKeepsShared();
    testMultiplyEqualRvalue();
    testMultiplyEqualChained();
}

void TestSet::testMultiplyEqualKeepsShared() {
    runTest(__func__, [this] {
        MySet<int> set1{1, 2, 3, 4};
        MySet<int> set2{3, 4, 5, 6};
        set1 *= set2;
        int i = 3;
        for (auto it = set1.iteratorBegin(); it != set1.iteratorEnd(); ++it) {
            check(it.value() == i);
            i++;
        }
    });
}

void TestSet::testMultiplyEqualRvalue() {
    runTest(__func__, [this] {
        MySet<int> set1{1, 2, 3, 4};
        set1 *= MySet<int>{3, 4, 5, 6};
        check(set1.getLength() == 2);
    });
}

void TestSet::testMultiplyEqualChained() {
    runTest(__func__, [this] {
        MySet<int> set1{1, 2, 3, 4, 5};
        MySet<int> set2{2, 3, 4, 5, 6};
        MySet<int> set3{3, 4, 5, 6, 7};
        set1 *= set2 *= set3;
        check(set1.getLength() == 3);
        check(set2.getLength() == 4);
    });
}

void TestSet::testOperatorDivideEqual() {
    testDivideEqualRemovesShared();
    testDivideEqualRvalue();
    testDivideEqualChained();
}

void TestSet::testDivideEqualRemovesShared() {
    runTest(__func__, [this] {
        MySet<int> set1{1, 2, 3, 4};
        MySet<int> set2{3, 4, 5, 6};
        set1 /= set2;
        int i = 1;
        for (auto it = set1.iteratorBegin(); it != set1.iteratorEnd(); ++it) {
            check(it.value() == i);
            i++;
        }
    });
}

void TestSet::testDivideEqualRvalue() {
    runTest(__func__, [this] {
        MySet<int> set1{1, 2, 3, 4};
        set1 /= MySet<int>{3, 4, 5, 6};
        check(set1.getLength() == 2);
    });
}

void TestSet::testDivideEqualChained() {
    runTest(__func__, [this] {
        MySet<int> set1{1, 2, 3, 4, 5};
        MySet<int> set2{1, 2};
        MySet<int> set3{1};
        set1 /= set2 /= set3;
        check(set1.getLength() == 4);
        check(set2.getLength() == 1);
    });
}

void TestSet::testOperatorAssignment() {
    testAssignmentCopiesElements();
    testAssignmentIndependent();
    testSelfAssignment();
    testAssignmentRvalue();
}

void TestSet::testAssignmentCopiesElements() {
    runTest(__func__, [this] {
        MySet<int> set1{1, 4, 2, 3};
        MySet<int> set2{9, 1, 2};
        set1 = set2;
        check(set1.getLength() == 3);
    });
}

void TestSet::testAssignmentIndependent() {
    runTest(__func__, [this] {
        MySet<int> set1{1, 2, 3};
        MySet<int> set2{4, 5, 6};
        set1 = set2;
        set2.add(7);
        check(!set1.contains(7));
    });
}

void TestSet::testSelfAssignment() {
    runTest(__func__, [this] {
        MySet<int> set{1, 2, 3};
        set = set;
        check(set.contains(1));
        check(set.contains(2));
        check(set.contains(3));
    });
}

void TestSet::testAssignmentRvalue() {
    runTest(__func__, [this] {
        MySet<int> set1{1, 4, 2, 3};
        set1 = MySet<int> {9, 1, 2};
        check(set1.getLength() == 3);
    });
}

void TestSet::testOperatorOutputStream() {
    testOutputStreamFormat();
    testOutputStreamFormatEmpty();
}

void TestSet::testOutputStreamFormat() {
    runTest(__func__, [this] {
        MySet<int> set{1, 2, 3};
        std::ostringstream ostream;
        ostream << set;
        check(ostream.str() == "{1, 2, 3}");
    });
}

void TestSet::testOutputStreamFormatEmpty() {
    runTest(__func__, [this] {
        MySet<int> set;
        std::ostringstream ostream;
        ostream << set;
        check(ostream.str() == "{ }");
    });
}

void TestSet::testIterator() {
    testIteratorBeginPointsToMin();
    testIteratorEndIsAtEnd();
    testIteratorEmptySet();
    testIteratorSum();
    testIteratorNext();
    testIteratorEqual();
}

void TestSet::testIteratorBeginPointsToMin() {
    runTest(__func__, [this] {
        MySet<int> set{8, 87, 9, 3};
        Iterator<int> iter(set);
        check(*iter == 3);
    });
}

void TestSet::testIteratorEndIsAtEnd() {
    runTest(__func__, [this] {
        MySet<int> set{8, 87, 9, 3};
        Iterator<int> iter = set.iteratorEnd();
        check(iter.isEnd());
    });
}

void TestSet::testIteratorEmptySet() {
    runTest(__func__, [this] {
        MySet<int> set;
        int count = 0;
        for (auto it = set.iteratorBegin(); it != set.iteratorEnd(); ++it)
            count++;
        check(count == 0);
    });
}

void TestSet::testIteratorSum() {
    runTest(__func__, [this] {
        MySet<int> set;
        set.add(7);
        set.add(9);
        set.add(14);
        int sum = 0;
        for (auto it = set.iteratorBegin(); it != set.iteratorEnd(); ++it)
            sum += *it;
        check(sum == 30);
    });
}

void TestSet::testIteratorNext() {
    runTest(__func__, [this] {
        MySet<int> set{1, 2, 3};
        auto it = set.iteratorBegin();
        check(it.value() == 1);
        it.next();
        check(it.value() == 2);
    });
}

void TestSet::testIteratorEqual() {
    runTest(__func__, [this] {
        MySet<int> set{1, 2, 3};
        auto it1 = set.iteratorBegin();
        auto it2 = set.iteratorBegin();
        check(it1 == it2);
    });
}

void TestSet::testDestructorAndRecreate() {
    runTest(__func__, [this] {
        {
            MySet<int> set{1, 2, 3};
        }
        MySet<int> set2{4, 5, 6};
        check(set2.getLength() == 3);
    });
}

void TestSet::showResults() {
    std::cout << "\n" <<
        "Total tests: " << succes + error << "\n" <<
        "Successful tests: " << succes << "\n" <<
        "Erroneous tests: " << error << std::endl;
}

void TestSet::runAllTests() {
    testConstructor();
    testGetLength();
    testAdd();
    testRemove();
    testContains();
    testClear();
    testGetRoot();
    testToArray();
    testUnion();
    testIntersection();
    testSubtract();
    testOperatorPlus();
    testOperatorIntersection();
    testOperatorSubtract();
    testOperatorPlusEqual();
    testOperatorMultiplyEqual();
    testOperatorDivideEqual();
    testOperatorAssignment();
    testOperatorOutputStream();
    testIterator();
    testDestructorAndRecreate();
    showResults();
}
