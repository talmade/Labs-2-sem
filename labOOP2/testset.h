#ifndef TESTSET_H
#define TESTSET_H

#include <functional>

class TestSet {
public:
    void runAllTests();
    bool hasFailed() const;
private:
    int succes = 0;
    int error = 0;
private:
    void check(bool condition);
    void runTest(const char* name, std::function<void()> func);
private:
    void testConstructor();
        void testDefaultConstructorEmpty();

        void testCopyConstructorContainsElements();
        void testCopyConstructorSameLength();
        void testCopyConstructorIndependent();

        void testMoveConstructorTransfersElements();
        void testMoveConstructorClearsSource();
        void testMoveConstructorEmptySource();

        void testInitializerListSkipsDuplicates();
        void testInitializerListEmpty();
private:
    void testGetLength();
        void testGetLengthEmpty();
        void testGetLengthFill();
private:
    void testAdd();
        void testAddIncreasesLength();
        void testAddSortedOrder();
        void testAddDuplicateIgnored();
private:
    void testRemove();
        void testRemoveAllElements();
        void testRemoveElementNotInSet();
        void testRemoveNonexistentElement();
        void testRemoveNodeWithTwoChildren();
private:
    void testContains();
        void testContainsExistingElement();
        void testContainsMissingElement();
        void testContainsEmptySet();
private:
    void testClear();
        void testClearEmptySet();
        void testClearRemovesAllElements();
        void testClearTwice();
        void testClearContainsFalse();
private:
    void testGetRoot();
        void testGetRootEmpty();
        void testGetRootValue();
private:
    void testToArray();
        void testToArrayNull();
        void testToArrayNotNull();
        void testToArraySortedOrder();
private:
    void testUnion();
        void testUnionWithEmpty();
        void testUnionPartiallyIdentical();
        void testUnionPartiallyIdenticalLength();
        void testUnionBothEmpty();
private:
    void testIntersection();
        void testIntersectionDisjointSets();
        void testIntersectionPartiallyIdentical();
        void testIntersectionPartiallyIdenticalContains();
        void testIntersectionBothEmpty();
private:
    void testSubtract();
        void testSubtractWithEmpty();
        void testSubtractPartiallyIdentical();
        void testSubtractPartiallyIdenticalContains();
        void testSubtractBothEmpty();
private:
    void testOperatorPlus();
        void testPlusDisjointSets();
        void testPlusOverlappingSets();
        void testPlusChained();
private:
    void testOperatorIntersection();
        void testMultiplyDisjointSets();
        void testMultiplyOverlappingSets();
        void testMultiplyChained();
private:
    void testOperatorSubtract();
        void testDivideRemovesShared();
        void testDivideSelfIsEmpty();
        void testDivideChained();
private:
    void testOperatorPlusEqual();
        void testPlusEqualAddsElements();
        void testPlusEqualRvalue();
        void testPlusEqualChained();
private:
    void testOperatorMultiplyEqual();
        void testMultiplyEqualKeepsShared();
        void testMultiplyEqualRvalue();
        void testMultiplyEqualChained();
private:
    void testOperatorDivideEqual();
        void testDivideEqualRemovesShared();
        void testDivideEqualRvalue();
        void testDivideEqualChained();
private:
    void testOperatorAssignment();
        void testAssignmentCopiesElements();
        void testAssignmentIndependent();
        void testSelfAssignment();
        void testAssignmentRvalue();
private:
    void testOperatorOutputStream();
        void testOutputStreamFormat();
        void testOutputStreamFormatEmpty();
private:
    void testIterator();
        void testIteratorBeginPointsToMin();
        void testIteratorEndIsAtEnd();
        void testIteratorEmptySet();
        void testIteratorSum();
        void testIteratorNext();
        void testIteratorEqual();
private:
    void testDestructorAndRecreate();
private:
    void showResults();
};

#endif // TESTSET_H
